#pragma once

#include "PCalc.h"

class PCalc_SP : public PCalc
{
public:
	PCalc_SP() {};
	PCalc_SP(unsigned int array_size);
	~PCalc_SP() {};

	void markNonPrimes() override;

	
};
