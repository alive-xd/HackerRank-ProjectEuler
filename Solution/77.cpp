#include <iostream>
#include <vector>

int main() {
  const unsigned int MaxNumber = 1000;
  // store number of ways to represent a number as a sum of primes
  std::vector < unsigned long long > combinations(MaxNumber + 1, 0);
  // degenerated case
  combinations[0] = 1;

  // store all primes
  std::vector < unsigned int > primes;
  for (unsigned int i = 2; i <= MaxNumber; i++) {
    bool isPrime = true;

    // test against all prime numbers we have so far (in ascending order)
    for (auto p: primes) {
      // next prime is too large to be a divisor ?
      if (p * p > i)
        break;

      // divisible ? => not prime
      if (i % p == 0) {
        isPrime = false;
        break;
      }
    }

    // only primes after this point ...
    if (!isPrime)
      continue;

    primes.push_back(i);

    // now add all solutions
    for (unsigned int pos = 0; pos <= MaxNumber - i; pos++)
      combinations[pos + i] += combinations[pos];
  }

  //#define ORIGINAL
  #ifdef ORIGINAL
  // find first number with more than 5000 combinations
  for (size_t i = 0; i < combinations.size(); i++)
    if (combinations[i] > 5000) {
      std::cout << i << std::endl;
      break;
    }
  #else
  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--) {
    // look up combinations
    unsigned int n;
    std::cin >> n;
    std::cout << combinations[n] << std::endl;
  }
  #endif

  return 0;
}