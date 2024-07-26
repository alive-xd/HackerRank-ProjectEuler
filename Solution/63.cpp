#include <iostream>

//#define ORIGINAL

// find all numbers where x^digits has digits digits (I'm loving that comment ...)
unsigned int check(unsigned int digits) {
  // numbe rof matches
  unsigned int count = 0;

  // unsigned long long isn't sufficient for the highest digits
  // a double has some rounding issues but they don't affect to result
  #ifdef ORIGINAL
  typedef double Number;
  #else
  typedef unsigned long long Number;
  #endif

  // range of valid numbers
  // from = 10^(digits-1)
  // to   = 10^digits - 1
  Number to = 1;
  for (unsigned int i = 1; i <= digits; i++)
    to *= 10;
  Number from = to / 10;
  to--;

  // try all single-digit base numbers
  for (unsigned int base = 1; base <= 9; base++) {
    // compute power = base ^ digits
    Number power = base;
    for (unsigned int i = 1; i < digits && power <= to; i++)
      power *= base;
    // could use C++'s pow(), too

    // right number of digits ?
    if (power >= from && power <= to) {
      count++;
      #ifndef ORIGINAL
      std::cout << std::fixed << power << std::endl;
      #endif
    }
  }

  return count;
}

int main() {
  #ifdef ORIGINAL
  // check all digits
  unsigned int count = 0;
  for (unsigned int digits = 1; digits <= 21; digits++) // I observed no results with more than 21 digits
    count += check(digits);
  std::cout << count << std::endl;

  #else

  // check only certain digits
  unsigned int digits = 9;
  std::cin >> digits;
  check(digits);
  #endif

  return 0;
}