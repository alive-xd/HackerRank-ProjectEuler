#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

int main() {
  unsigned long long limit = 4000000;
  std::cin >> limit;

  #define ORIGINAL
  #ifdef ORIGINAL
  // 12 primes are enough for the original problem, I added a few more for the Hackerrank version
  const unsigned int NumPrimes = 12;
  // a short list of primes
  unsigned int primes[] = {
    2,
    3,
    5,
    7,
    11,
    13,
    17,
    19,
    23,
    29,
    31,
    37
  };
  #else
  const unsigned int NumPrimes = 18;
  // a short list of primes
  unsigned int primes[] = {
    2,
    3,
    5,
    7,
    11,
    13,
    17,
    19,
    23,
    29,
    31,
    37,
    41,
    43,
    47,
    53,
    59,
    61
  };
  #endif

  // use 1 as a "seed" value (all its primes' exponents are zero)
  typedef std::vector < unsigned char > Exponents;
  std::map < long double, Exponents > todo = {
    {
      1,
      Exponents(NumPrimes, 0)
    }
  };

  while (true) {
    // pick the smallest value and its exponents
    auto current = todo.begin();
    auto value = current -> first;
    auto exponents = current -> second;

    // remove from todo list
    todo.erase(current);

    // find number of factorizations
    unsigned long long uniqueFactors = 1;
    for (auto x: exponents)
      uniqueFactors *= 2 * x + 1;
    // a*b = b*a => divide number of factorizations by 2
    uniqueFactors++;
    uniqueFactors /= 2;

    // stop ?
    if (uniqueFactors >= limit) {
      std::cout << std::fixed << std::setprecision(0) << value << std::endl;
      break;
    }

    // increment each primes' exponent by 1 and append new value to todo list
    for (size_t i = 0; i < exponents.size(); i++) {

      exponents[i]++;
      value *= primes[i];

      todo[value] = exponents;
      // note: std::map prunes duplicates automatically
    }
  }

  return 0;
}