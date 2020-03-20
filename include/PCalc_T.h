#pragma once

#include "PCalc.h"

#include <vector>
#include <queue>
#include <thread>
#include <mutex>

class PCalc_T : public PCalc
{
public:
	PCalc_T() {};
	PCalc_T(unsigned int count, unsigned int maxThreads);
	~PCalc_T() {};

	void markNonPrimes() override;

	std::vector<bool> sieveList_;
	std::queue<unsigned int> toSieve_;
	std::vector<unsigned int> primes_;

	unsigned int	activeThreadCount_;
	unsigned int	maxThreads_;
	unsigned int	current_;
	unsigned int	stopPoint_;

	std::mutex	m_;
	
	// threads
	void manager(); // creates workers from queue 
	bool verify(unsigned int x); // checks if a number is prime to add to queue 
	void worker(unsigned int prime, bool *p); // works

	
};
