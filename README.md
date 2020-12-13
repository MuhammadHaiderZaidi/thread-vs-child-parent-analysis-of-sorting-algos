Results:
The below three graphs show the time comparison of the three algorithms under various data range using both approaches.













![alt text](https://i.ibb.co/cJg6Djr/1.png)



For bubble sort as compared to other algorithms the average time for both the approaches were more however threads were proven to be faster.
 


















![alt text](https://i.ibb.co/XFgBfjV/3.png)



For thread the quick sort was efficient as compared to process the time variance under different data was small

 











![alt text](https://i.ibb.co/CwjMLCV/4.png)


Since the data was randomly generated and merge sort works for both worst case and best case well enough therefore the approach through threads was the most efficient and the curve is very small as compared to that of process.
 




CASE STUDY:

These different results were generated due the following difference between process and threads




Process:
-heavy weight and resource intensive
-process switching needs interaction with operating system
-in multiple processing environments each process executes the same code but has its own memory and file resources
-if one process is blocked then no other process can execute until the first process is unblocked
-multiple processes without using threads use more resources
-in multiple processes each process operates independently of the others


Thread:
-thread is light weight taking lesser resources than a process
-thread switching does not need to interact with operating system
-all threads can share same set of open files, child processes
-while one thread is blocked and waiting, second thread in the same task can run
-multiple threaded processes use fewer resources
-One thread can read, write or change another thread's data.




CONCLUSION:

To conclude since threads are faster than processes sorting algorithms using threads took less time then that of processes.
 







                                                             
