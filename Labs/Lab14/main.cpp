#include <iostream>
#include <thread>
#include <algorithm>
#include "SharedQueue.h"
#include "Timer.h"

struct Range {
	uint64_t from, to;
};

bool IsPerfectNumber(uint64_t number)
{
	uint64_t limit = number/2;
	uint64_t sum = 0;
	for (uint64_t x = 1; x <= limit; x++)
	{
		if (0 == number%x)
			sum += x;
	}
	return (sum == number);
}

void ThreadWorker(SharedQueue<Range> *workQueue, SharedQueue<uint64_t> *resultQueue)
{
	Range r;
	while (true)
	{
		// read work from queue
		while (workQueue->Remove(r) == false)
		{ std::this_thread::yield(); }
		
		// if from==to, then this is a quit message; we are done
		if (r.from == r.to)
		{
			break;
		}

    // compute whether each number in Range is a perfect number
    // and put perfect numbers into the result queue
		for (uint64_t x = r.from; x < r.to; x++)
		{
			if (IsPerfectNumber(x))
				resultQueue->Add(x);
		}
		
	}
}

void FindPerfectNumbers(uint64_t maxValue, int workSize, unsigned numThreads)
{
	SharedQueue<Range> workQueue;
	SharedQueue<uint64_t> resultQueue;
	Timer t;
	t.StartTimer();
	
	std::thread **threads;
	threads = new std::thread*[numThreads];
	for (int x = 0; x < numThreads; x++)
	{
		threads[x] = new std::thread(ThreadWorker, &workQueue, &resultQueue);
	}
	
	for (uint64_t x = 1; x < maxValue; x+=workSize)
	{
		workQueue.Add({x, std::min(x+workSize, maxValue)});
	}
	
	for (int x = 0; x < numThreads; x++)
	{
		workQueue.Add({0,0});
	}
	
	for (int x = 0; x < numThreads; x++)
	{
		threads[x]->join();
		delete threads[x];
	}
	delete [] threads;
	
	std::cout << "Perfect numbers:" << std::endl;
	while (!resultQueue.IsEmpty())
	{
		uint64_t result;
		if (resultQueue.Remove(result))
			std::cout << result << std::endl;
	}
	std::cout << "Finding perfect numbers from 1 to " << maxValue << " took " << t.EndTimer() << " seconds.\n";
	std::cout << numThreads << " threads; work unit " << workSize << " items." << std::endl;
}

int main(int argc, const char * argv[])
{
	unsigned num_threads = std::thread::hardware_concurrency();
	
	FindPerfectNumbers(10000, 10000, 1);
	
	FindPerfectNumbers(10000, 1, 1);
	FindPerfectNumbers(10000, 1, num_threads);
	FindPerfectNumbers(10000, 100, num_threads);
	
	FindPerfectNumbers(100000, 100, num_threads);
	
	// This will take a long time for most machines, but try it out to see yourself!
	// FindPerfectNumbers(1000000, 100, num_threads);
	// This will find the next perfect number, but will take too long in practice
	// FindPerfectNumbers(34000000, 1000, num_threads);
	
	return 0;
}

/**
 * Report here:
 *
 * What are the runtimes for each of the 5 calls above?
 * Can you explain the differences in runtime for computing
 * perfect numbers within the first 10,000 elements?
 *
 *
 *
 *
 *
 *
 */
