READ ME 

Group: 
Taylor Caswell 
Matthew Curuano
Eric Evans
Mesuilame Mataitoga
Radhika Mitra 


The following instructions shows how to compile and build Project 2 source code: 

1. 
Replace:
/usr/src/servers/pm/schedule.c with our_group/pm/schedule.c
/usr/src/servers/sched/schedule.c with our_group/sched/schedule.c
/usr/src/servers/sched/schedproc.h with our_group/sched/schedproc.h

2.
In sched/schedule.c set #define STATIC_LOTTERY  (line 33) to 0 or 1 
If set to 0 static lottery will be off, and dynamic lottery will be executed
If set to 1 static lottery will be executed and dynamic lottery will be off. 

3. 
Launch Minix and run the following commands:
# cd /usr/src/tools
# make install

4. 
Now run custom build.


The following instructions is for running the test cases: 

NOTE: STATIC_LOTTERY found in sched/schedule.c must be set to 1 for test 1-4

Run the commands: 
make test1 
make test2
make test3
make test4

NOTE: STATIC_LOTTERY found in sched/schedule.c must be set to 0 for test5and6 

make test5and6
