# philosophers_42
This repository is dedicated to the Philosophers project, which is the second project of Rank 3.

I want to make different approach to this project, which is I separated project to small
parts. In these small parts contain threads, deadlock and etc.

🧩 1. the base of threads
Goal: To understand how pthread_create and pthread_join work.
Tasks:
 * To create 2 threads and each of them prints the name of the thread in 1 second
 * and should wait 1 second
 -- A thing to learn: How thread works and what parallel output looks like

🧩 2. the arguments of thread
Goal: To learn how to send arguments to each thread
Tasks:
 * Create 3 threads, pass to each thread the type of integer and print it this integer inside of thread.
 -- A thing to learn: how to pass the info to thread( void *arg ).