#include <cstring>
#include <stdexcept>
#include <fstream>
#include <iostream>

#include <PCalc.h>

/************************************************************************************************
 * PCalc (constructor) - Creates an array of primelist boolean objects with the size of
 *                       array_size and initializes them all to true 
 ************************************************************************************************/

PCalc::PCalc(unsigned int array_size):asize(array_size), primelist(new bool[array_size]) {

   // initialize the array of numbers with true 
   memset(primelist, 1, sizeof(bool)*asize);
}


/************************************************************************************************
 * PCalc (destructor) - deletes the primelist array
 ************************************************************************************************/

PCalc::~PCalc() {
   cleanup();
}

/************************************************************************************************
 * cleanup - cleans up memory from this object
 ************************************************************************************************/

void PCalc::cleanup() {
   if (primelist != NULL)
      delete[] primelist;
   primelist = NULL;
}

/************************************************************************************************
 * operator [] - retrieves a reference (can be modified) to the prime boolean at index x
 *                      
 ************************************************************************************************/

bool &PCalc::operator [] (unsigned int x){
   if (x > asize) {
      throw std::range_error("primelist array index out of bounds");
   }

   return primelist[x];
}

/************************************************************************************************
 * at - retrieves a reference (can be modified) to the prime boolean at index x
 *
 ************************************************************************************************/

bool &PCalc::at(unsigned int x) {
   if (x > asize) 
      throw std::range_error("primelist array index out of bounds");

   return primelist[x];
}

/************************************************************************************************
 * printPrimes - outputs the prime values to the file specified
 *
 *    Params:  filename - the path/filename of the output file
 *
 ************************************************************************************************/

void PCalc::printPrimes(const char *filename) {
   std::fstream outfile;

   outfile.open(filename, std::fstream::out);

   if (!outfile.is_open()) {
      std::cout << "Failed to open file " << filename << " for writing.";
      return;      
   }

   for (unsigned int i=0; i<asize; i++) {
      if (primelist[i])
	 outfile << i << "\n";
   }

   outfile.close();
}

