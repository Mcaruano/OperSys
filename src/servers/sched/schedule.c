/* CHANGED: 5/1/2014
 * This file contains the scheduling policy for SCHED
 *
 * The entry points are:
 *   do_noquantum:        Called on behalf of process' that run out of quantum
 *   do_start_scheduling  Request to start scheduling a proc
 *   do_stop_scheduling   Request to stop scheduling a proc
 *   do_nice          Request to change the nice level on a proc
 *   init_scheduling      Called from main.c to set up/prepare scheduling
 */
#include "sched.h"
#include "schedproc.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <minix/com.h>
#include <machine/archtypes.h>
#include "kernel/proc.h" /* for queue constants */

PRIVATE timer_t sched_timer;
PRIVATE unsigned balance_timeout;

#define BALANCE_TIMEOUT 5 /* how often to balance queues in seconds */

FORWARD _PROTOTYPE( int schedule_process, (struct schedproc * rmp)  );
FORWARD _PROTOTYPE( void balance_queues, (struct timer *tp)     );

#define DEFAULT_USER_TIME_SLICE 200
/* START CHANGES */
#define WINNER_QUEUE 13
#define LOSER_QUEUE 14
#define STATIC_LOTTERY 0  /*Change to 1 to run static lottery */
/* END CHANGES */

/*===========================================================================*
 *              do_noquantum                     *
 *===========================================================================*/

PUBLIC int do_noquantum(message *m_ptr)
{

    register struct schedproc *rmp;
    int rv, proc_nr_n, proc_nr;

    /* START CHANGES */
    int ticket_sum = 0;
    int random_val = 0;
    srand(time(NULL));

    if (sched_isokendpt(m_ptr->m_source, &proc_nr_n) != OK) {
        printf("SCHED: WARNING: got an invalid endpoint in OOQ msg %u.\n",
        m_ptr->m_source);
        return EBADEPT;
    }

    rmp = &schedproc[proc_nr_n];

    if(!STATIC_LOTTERY){
        /* If this process is in the loser queue, if there is a process in the winner queue, give the process in the winning queue a ticket */
        if(rmp->priority == LOSER_QUEUE){
            for (proc_nr=0, rmp=schedproc; proc_nr < NR_PROCS; proc_nr++, rmp++) {
                if (rmp->flags & IN_USE) {
                    if (rmp->priority == WINNER_QUEUE) {
                        /* ATTEMPTED OPTIMIZATION */
                        /*rmp->block_count++;
                        if(rmp->block_count == 5){
                            rmp->block_count = 0; 
                            rmp->num_tickets++;
                            if (rmp->num_tickets > 100) {
                                rmp->num_tickets = 100;
                            }
                        }*/

                        rmp->num_tickets++;
                        if (rmp->num_tickets > 100) {
                            rmp->num_tickets = 100;
                        }

                        printf("INCREMENT: Endpoint: %d, num_tickets = %d\n", rmp->endpoint, rmp->num_tickets);
                    }
                }
            }
        }

        /* If this process used up its quantum in the winner queue, take away a ticket */
        /* Attempted optimization: only decrement a ticket if a process has used its entire quantum from winner queue 5 times */
        else if(rmp->priority == WINNER_QUEUE){
            rmp->block_count++;
            if (rmp->block_count == 5) {
                rmp->block_count = 0;
                rmp->num_tickets--;
                if (rmp->num_tickets < 1) {
                    rmp->num_tickets = 1;
                }
                printf("DECREMENT: Endpoint: %d, num_tickets = %d\n", rmp->endpoint, rmp->num_tickets);
            }
        }

        rmp = &schedproc[proc_nr_n];
    }

    if(rmp->priority >= 13){

        rmp->priority = LOSER_QUEUE;

        if ((rv = schedule_process(rmp)) != OK) {
            return rv;
        }

        /* Iterate through all processes in loser queue, sum up all of their num_tickets */
        for (proc_nr=0, rmp=schedproc; proc_nr < NR_PROCS; proc_nr++, rmp++) {
            if (rmp->flags & IN_USE) {
                if (rmp->priority == LOSER_QUEUE) {
                    ticket_sum += rmp->num_tickets;
                }
            }
        }

        /* Generate a random number from 1 - ticket_sum */
        random_val = (rand()%ticket_sum) + 1;

        /* Iterate through all processes again in the user queue, and subtract all of their num_tickets from the random number */
        for (proc_nr=0, rmp=schedproc; proc_nr < NR_PROCS; proc_nr++, rmp++) {
            if (rmp->flags & IN_USE) {
                if (rmp->priority == LOSER_QUEUE) {
                    random_val -= rmp->num_tickets;
                    /* When the random number hits 0 or less, go with that process */
                    if(random_val <= 0){
                        rmp->priority = WINNER_QUEUE;
                        break;
                    }
                }
            }
        }
    }
    /* END CHANGES */

    if ((rv = schedule_process(rmp)) != OK) {
        return rv;
    }

    return OK;
}

/*===========================================================================*
 *              do_stop_scheduling               *
 *===========================================================================*/
PUBLIC int do_stop_scheduling(message *m_ptr)
{
    register struct schedproc *rmp;
    int rv, proc_nr_n;

    /* check who can send you requests */
    if (!accept_message(m_ptr))
        return EPERM;

    if (sched_isokendpt(m_ptr->SCHEDULING_ENDPOINT, &proc_nr_n) != OK) {
        printf("SCHED: WARNING: got an invalid endpoint in OOQ msg "
        "%ld\n", m_ptr->SCHEDULING_ENDPOINT);
        return EBADEPT;
    }

    rmp = &schedproc[proc_nr_n];
    rmp->flags = 0; /*&= ~IN_USE;*/

    return OK;
}

/*===========================================================================*
 *              do_start_scheduling              *
 *===========================================================================*/
PUBLIC int do_start_scheduling(message *m_ptr)
{
    register struct schedproc *rmp;
    int rv, proc_nr_n, parent_nr_n, nice;
    
    /* we can handle two kinds of messages here */
    assert(m_ptr->m_type == SCHEDULING_START || 
        m_ptr->m_type == SCHEDULING_INHERIT);

    /* check who can send you requests */
    if (!accept_message(m_ptr))
        return EPERM;

    /* Resolve endpoint to proc slot. */
    if ((rv = sched_isemtyendpt(m_ptr->SCHEDULING_ENDPOINT, &proc_nr_n))
            != OK) {
        return rv;
    }

    rmp = &schedproc[proc_nr_n];

    /* Populate process slot */
    rmp->endpoint     = m_ptr->SCHEDULING_ENDPOINT;
    rmp->parent       = m_ptr->SCHEDULING_PARENT;
    rmp->max_priority = (unsigned) m_ptr->SCHEDULING_MAXPRIO;
    if (rmp->max_priority >= NR_SCHED_QUEUES) {
        return EINVAL;
    }
    
    switch (m_ptr->m_type) {

    case SCHEDULING_START:
        /* We have a special case here for system processes, for which
         * quantum and priority are set explicitly rather than inherited 
         * from the parent */
        rmp->priority   = rmp->max_priority;
        rmp->time_slice = (unsigned) m_ptr->SCHEDULING_QUANTUM;
        break;
        
    case SCHEDULING_INHERIT:
        /* Inherit current priority and time slice from parent. Since there
         * is currently only one scheduler scheduling the whole system, this
         * value is local and we assert that the parent endpoint is valid */
        if ((rv = sched_isokendpt(m_ptr->SCHEDULING_PARENT,
                &parent_nr_n)) != OK)
            return rv;
        
        /* START CHANGES */
        /* rmp->priority = schedproc[parent_nr_n].priority; */
        rmp->priority = LOSER_QUEUE;
        rmp->time_slice = schedproc[parent_nr_n].time_slice;
        /* printf("The time_slice given to this process is %d\n", rmp->time_slice); */
        rmp->num_tickets = 20;
        rmp->block_count = 0; /* ATTEMPTED OPTIMIZATION */
        /* END CHANGES */
        break;
        
    default: 
        /* not reachable */
        assert(0);
    }

    /* Take over scheduling the process. The kernel reply message populates
     * the processes current priority and its time slice */
    if ((rv = sys_schedctl(0, rmp->endpoint, 0, 0)) != OK) {
        printf("Sched: Error taking over scheduling for %d, kernel said %d\n",
            rmp->endpoint, rv);
        return rv;
    }

    rmp->flags = IN_USE;

    /* Schedule the process, giving it some quantum */
    if ((rv = schedule_process(rmp)) != OK) {
        printf("Sched: Error while scheduling process, kernel replied %d\n",
            rv);
        return rv;
    }

    /* Mark ourselves as the new scheduler.
     * By default, processes are scheduled by the parents scheduler. In case
     * this scheduler would want to delegate scheduling to another
     * scheduler, it could do so and then write the endpoint of that
     * scheduler into SCHEDULING_SCHEDULER
     */

    m_ptr->SCHEDULING_SCHEDULER = SCHED_PROC_NR;

    return OK;
}

/*===========================================================================*
 *              do_nice                                                     *
 *===========================================================================*/
PUBLIC int do_nice(message *m_ptr)
{
    struct schedproc *rmp;
    int rv;
    int proc_nr_n;
    unsigned new_q, old_q, old_max_q;

    /* check who can send you requests */
    if (!accept_message(m_ptr))
        return EPERM;

    if (sched_isokendpt(m_ptr->SCHEDULING_ENDPOINT, &proc_nr_n) != OK) {
        printf("SCHED: WARNING: got an invalid endpoint in OOQ msg "
        "%ld\n", m_ptr->SCHEDULING_ENDPOINT);
        return EBADEPT;
    }

    /* add tickets based on nice call, with bounds 1 <= tickets <= 100 */
    rmp = &schedproc[proc_nr_n];
    rmp->num_tickets -= m_ptr->SCHEDULING_MAXPRIO;

    /* START CHANGES */
    if (rmp->num_tickets > 100) {
        rmp->num_tickets = 100;
    }

    if (rmp->num_tickets < 1) {
        rmp->num_tickets = 1;
    }
    /* END CHANGES */
    
    new_q = (unsigned) m_ptr->SCHEDULING_MAXPRIO;
    if (new_q >= NR_SCHED_QUEUES) {
        return EINVAL;
    }

    /* Store old values, in case we need to roll back the changes */
    old_q     = rmp->priority;
    old_max_q = rmp->max_priority;

    /* START CHANGES */
    /* Update the proc entry and reschedule the process */
    /* rmp->max_priority = rmp->priority = new_q; */
    /* END CHANGES */

    if ((rv = schedule_process(rmp)) != OK) {
        /* Something went wrong when rescheduling the process, roll
         * back the changes to proc struct */
        rmp->priority     = old_q;
        rmp->max_priority = old_max_q;
    }

    return rv;
}

/*===========================================================================*
 *              schedule_process                 *
 *===========================================================================*/
PRIVATE int schedule_process(struct schedproc * rmp)
{
    int rv;

    if ((rv = sys_schedule(rmp->endpoint, rmp->priority,
            rmp->time_slice)) != OK) {
        printf("SCHED: An error occurred when trying to schedule %d: %d\n",
        rmp->endpoint, rv);
    }

    return rv;
}


/*===========================================================================*
 *              start_scheduling                 *
 *===========================================================================*/

PUBLIC void init_scheduling(void)
{
    balance_timeout = BALANCE_TIMEOUT * sys_hz();
    init_timer(&sched_timer);
    set_timer(&sched_timer, balance_timeout, balance_queues, 0);
}

/*===========================================================================*
 *              balance_queues                   *
 *===========================================================================*/

/* This function in called every 100 ticks to rebalance the queues. The current
 * scheduler bumps processes down one priority when ever they run out of
 * quantum. This function will find all proccesses that have been bumped down,
 * and pulls them back up. This default policy will soon be changed.
 */
PRIVATE void balance_queues(struct timer *tp)
{
    struct schedproc *rmp;
    int proc_nr;
    int rv;

    /* START CHANGES */

    /*for (proc_nr=0, rmp=schedproc; proc_nr < NR_PROCS; proc_nr++, rmp++) {
        if (rmp->flags & IN_USE) {
            if (rmp->priority > rmp->max_priority) {

                rmp->priority -= 1; /* increase priority *//*
                schedule_process(rmp);

            }
        }
    }*/

    /* END CHANGES */

    set_timer(&sched_timer, balance_timeout, balance_queues, 0);
}
