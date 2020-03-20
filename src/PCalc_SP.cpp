#include "PCalc_SP.h"
#include <cmath>

PCalc_SP::PCalc_SP(unsigned int array_size) 
	: PCalc(array_size)
{

}

void PCalc_SP::markNonPrimes()
{
	// Start with 0 and 1 as false
	auto p = primelist;
	p[0] = false;
	p[1] = false;
	p[2] = true;
	
	unsigned int startingPoint = 2;
	
	// we only need to sieve to here, since any thing above here if composite, has a factor below here
	unsigned int stopPoint = static_cast<unsigned int>(std::sqrt(asize)) + 10; 
	for(unsigned int x = startingPoint; x < stopPoint; x++)
	{
		if(p[x]) // x is prime, so sieve on it
		{
			auto y = 2*x;
			if(y < x) 
			{
				break; // should never get here since sqrt(2x) < x \-/ numbers > 2 
			}
			while(y < asize)
			{
				p[y] = false;
				y += x;
			}
		}
	}
}
