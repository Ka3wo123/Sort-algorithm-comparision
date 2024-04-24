# Insight into execution time of sorting algorithms with different optimization manners
When we discuss about sorting algorithms I am sure that most of programmers tend to use the simplest one. But they aren't always as efficient as they could be thought.

I decided to compare sort algorithms' execution times using different optimization manners like different sort algorithms, single/multithreading and GPU usage. 

My CPU - 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz 2.42 GHz \
My GPU - Intel(R) Iris(R) Xe Graphics - CUDA doesn't run on non-Nvidia GPUs so I will use Google Colab.

## Simple sorting
### Bubble sort
At the very beggining I started sorting not so big array (2^10 = 1_024 elements) using bubble sort on single thread. \
![bubble sort](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/bubble%20sort%201.png) \
5 milliseconds don't scare. But it could be faster. Let's check much bigger array (2^17 = 131_072).
![bubble sort 2](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/bubble%20sort%20useless.png) \
**Over 32 SECONDS**. Whereas bubble sort "could be" efficient for smaller amount of data it is definietly not worth for larger amounts.

### Quick sort
Another sort algorithm is quick sort. Let's check how it copes with 2^10=1_024 elements and compare it with bubble sort. \
![quick sort](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/quick%20sort%202%5E10.png) \
As we see it is faster than bubble sort algorithm. \
\
Bring larger array 2^17=131_072 \
![quick sort 2](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/quick%20sort%202%5E17.png)  \
Also it is pretty fast - bubble sort have made us wait half a minute... \
\
Shall we see efficency for 2^25 = 33_554_432? \
![quick sort 3](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/quick%20sort%202%5E25.png) \
Although we need to wait 16 seconds when algorithm accomplishes the work it is more worth than for bubble sort which I didn't even launch with so enormous array size.

## Tune it up with multithreading
Nowadays processors are built with several cores. It opens new possibilities for optimizing calculations which contribute to reduction of execution time. \
\
❗(Crucial info - increasing number of threads doesn't mean that exe time will be shorter. Threads need to be created and it also takes time. Imagine creating million of threads for million-size array. It will be faster to start sorting on single thread rather than that number. Thus number of threads needs to be set properly to obtain the best results).❗
### Bubble sort with multiple threads
We can run bubble sort algorithm on multiple threads, previous was launch on single thread. Check out the execution time for 2^17 = 131_072 and maybe 8 threads. \
![bubble sort threads](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/bubble%20sort%208%20threads.png) \
Little over one second. That is much better than on single thread but still quick sort was faster with single thread previously. \
\
As I stated in crucial info, number of threads needs to be set in best way to achive best results. I got them for 128 threads.  
![bubble sort threads 2](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/bubble%20sort%20128%20threads.png)  
Almost ten times faster.
### Quick sort with multiple threads
Now it is time to tune up quick sort by launching it on multiple threads. Let's start with 2^25 = 33_554_432 and set 8 threads (Got best results on this). \
![quick sort threads](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/quick%20sort%208%20threads%202%5E25.png) \
Pretty fast regarding to previous performance. Let's see how it would cope with bigger size 2^30 = 1_073_741_824, 128 threads. \
![quick sort threads 2](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/quick%20sort%20128%20threads%202%5E30.png) \
For one billion it took almost **10 MINUTES**. I didn't check other numbers of threads because since now my computer started to freeze. \
\
As it can be seen multithreading is very helpful for optimizing execution time, but when it is related to vastness in implementation context we need to arm ourselves with patience.

## GPU to the rescue
It isn't the end. GPUs are much more powerful than CPUs when it is about computing. It is possible that code can be run on it resulting with faster computations. \
I used Google Colab due to the lack of Nvidia graphic card. 

To run CUDA file in Colab follow steps:
- upload your_file.cu to the ./content/src folder (src should be created manually)
- then run sequentially
```
!pwd
cd ./src
ls
!nvcc --gpu-architecture=sm_70 --device-c your_file.cu #
!nvcc --gpu-architecture=sm_70 your_file.o #
!./a.out
```

### Quick sort using GPU
2^30 array size took almost 10 minutes for 128 threads on CPU. Now it is time to get to know the exe time on GPU with the same parameters. \
![quick sort cuda](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/quick%20sort%20128%20threads%202%5E30%20cuda.png) \
"Only" two minutes. Comparing to CPU time it is 5x faster. Sounds great. What about other number of threads we can set for the same array size. \
\
64 threads: \
![quick sort cuda 2](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/quick%20sort%2064%20threads%202%5E30%20cuda.png) \
\
1024 threads: \
![quick sort cuda 3](https://github.com/Ka3wo123/Sort-comparision/blob/master/images/quick%20sort%201024%20threads%202%5E30%20cuda.png) 
\
As it can be seen the most optimistic scenario is for 128 threads. It proves that proper selection of threads number is important if we want to obtain the best time results.



