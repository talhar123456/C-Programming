1. A common variable counter is incremented from 5 threads 5000 times. The result is 24756. How is that possible?

Ans. It might be possible dur to lack of synchronization, resulting in a race condition where threads overwrite each other's changes. 

2. How could you correct the problem? Provide a short code example.

Ans. 
std::mutex myMutex;
int commonVariable = 0;
{
    std::lock_guard<std::mutex> lock(myMutex);
    commonVariable += 1; // Increment or modify
}

3. Why should lock_guard be preferred to explicit locking?

Ans. lock_guard is preferred cause it automatically releases the lock when it goes out of scope preventing accidental dealocks.

4. What is an alternative to locking variables and why? 

Ans. alternative can be using atomic variables, ensuring atomic operations without expliciti locks for simple operaiotns like increments.

5. Can multiple threads access a variable that is read-only safely without locking?

Ans. yes if variable is read only multiple threads can be safely access it withiut locking.

6. Which type of mutex would you use if you have multiple threads reading from the same value and only one writing to the value? Provide a short code exam-
ple.

Ans. 
std::shared_mutex myMutex;
int commonValue = 0;
{
    std::shared_lock<std::shared_mutex> lock(myMutex);
}
{
    std::unique_lock<std::shared_mutex> lock(myMutex);
}


7. How would you parallelize a for loop with the Intel TBB? How with OpenMP?

Ans. with Intel TBB: 'tbb::parallel_for' for loop parallelization. with OpenMP: '#pragma omp parallel for'.
