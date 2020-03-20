#pragma once

/******************************************************************************************
 * PCalc - Parent class for prime number calculation, up to the max size of an unsigned int
 *  	   (based on max size of an array). This class is an abstract class and not meant
 *  	   to be instantiated. Students should overload the MarkNonPrimes() function and,
 *  	   depending on their implementation, may want to overload cleanup().
 *
 *  	   PCalc(Const): takes in the array size (max number to count up to) and initializes
 *  	   ~PCalc(Dest): cleans up memory (deletes array)
 *
 *  	   Operator [] - returns a reference to an array element for reading or writing
 *  	   printPrimes - writes all marked prime numbers from the array to a newline-
 *  	                 delineated file
 *
 *****************************************************************************************/

class PCalc { 
   public:
      virtual ~PCalc();

      // Overload me!
      virtual void markNonPrimes() = 0;

      void printPrimes(const char *filename);

      // Retrieve the prime boolean element at x
      bool &operator [] (unsigned int x);
      bool &at(unsigned int x);

      unsigned int array_size() { return asize; };

      // if you overload, don't forget to call me
      virtual void cleanup();

//   unnecessary
//   protected:

      // Do not forget, your constructor should call this constructor
      PCalc(unsigned int array_size);

//   private:
 
      PCalc() {};

      // Stuff to be left alone
      unsigned int asize;
      bool *primelist;
};
