#include "PCalc_T.h"
#include <cmath>

#include <thread>
#include <iostream>

PCalc_T::PCalc_T(unsigned int count, unsigned int maxThreads)
	: PCalc(count),
	  maxThreads_(maxThreads),
	  activeThreadCount_(0)
{

}

void PCalc_T::markNonPrimes()
{
	// I am assuming the management thread does not count towards the max threads limit.
	manager();
}

bool PCalc_T::verify(unsigned int x)
{
	auto p = primelist;
	unsigned int stopPoint = static_cast<unsigned int>(std::sqrt(x)) + 1;
	for(auto i = 0; i < stopPoint; i++) // get up to sqrt(x), but not over it
	{
		if(p[i] && !(x % i)) // if i is prime, and x is a product of it
		{
			return false;
		}
	}
	return true;
}

void PCalc_T::manager()
{
	// initialize some values
	bool running = true;
	stopPoint_ = static_cast<unsigned int>(std::sqrt(asize)) + 1;
	activeThreadCount_ = 0;
	auto p = primelist;
	p[0] = false;
	p[1] = false;
	current_ = 2;

	while(running)
	{
		// First, check how many threads are available
		auto available = maxThreads_ - activeThreadCount_;
		if(available == 0)
		{
			// no threads are available, we don't need to find work to do.
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue; // try again
		}
			
		// Second, check for that many next primes and put into queue
		auto count = 0;
		while(count < available)
		{
			if(verify(current_))
			{
				toSieve_.push(current_);
				count++; // we got work!
			}
			current_++;
			if(current_ >= stopPoint_)
			{
				running = false;
				break; // don't need to create work beyond this point
			}
		}

		// Third, assign work for threads
		while(!toSieve_.empty())
		{
			std::unique_lock<std::mutex> lock(m_);
			activeThreadCount_++;
			std::thread(&PCalc_T::worker, this, toSieve_.front(), p).detach(); //don't need to keep rack of except in thread count
			toSieve_.pop(); // remove from work list
		}
	}

	// wait for all active threads to finish
	while(activeThreadCount_ > 0);
	
	// done;
	return;
}

void PCalc_T::worker(unsigned int prime, bool *p)
{
	for(auto x = 2*prime; x < asize; x += prime)
	{
		p[x] = false;
	}

	// signal that this work is done
	std::unique_lock<std::mutex> lock(m_);
	activeThreadCount_--;
	//std::cout << "Finished: " << prime << ", " << activeThreadCount_ << " threads still working" << std::endl;
}

