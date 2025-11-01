This is a very fun project. 

When we implement ticket's lock, different solution will have a different performance. 

spinlock is fast. But when user try to access critical section too much, the system will hang on. 

when I use sleep function inside while loop, too much context switch, we don't know who will be the next ticket holder. 

Yield maybe a good solution. It is worth to have a yield syscall to test. 

