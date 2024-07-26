#include <iostream>
#include <vector>
#include <algorithm>

// wheel-based prime test from my [toolbox](../toolbox/#primetest-wheel)
bool isPrime(unsigned int x) {
  // prime test for 2, 3 and 5
  if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0)
    return x == 2 || x == 3 || x == 5;

  // wheel with size 30 (=2*3*5):
  // test against 30m+1, 30m+7, 30m+11, 30m+13, 30m+17, 30m+19, 30m+23, 30m+29
  // their deltas/increments are:
  const unsigned char Delta[] = {
    6,
    4,
    2,
    4,
    2,
    4,
    6,
    2
  };
  // start with 7, which is 30*0+7
  unsigned int i = 7;
  // 7 belongs to the second test group
  unsigned int pos = 1;

  // check numbers up to sqrt(x)
  while (i * i <= x) {
    // not prime ?
    if (x % i == 0)
      return false;

    // skip forward to next test divisor
    i += Delta[pos];
    // next delta/increment
    pos = (pos + 1) & 7;
  }

  // passed all tests, must be a prime number
  return x > 1;
}

int main() {
  // find all matching primes up to this limit
  unsigned int limit = 100000000;

  // store all matching primes
  std::vector < unsigned int > matches;

  // start with a=1
  unsigned int a = 1;
  while (true) {
    // (a+1)^3 - a^3 = 3a^2 + 3a + 1
    auto p = 3 * a * a + 3 * a + 1;
    // too big ?
    if (p >= limit)
      break;

    // found one more prime ?
    if (isPrime(p))
      matches.push_back(p);

    // keep going ...
    a++;
  }

  // process STDIN
  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--) {
    std::cin >> limit;
    // find highest position located before the limit (matches are sorted, should use binary search)
    auto lower = std::lower_bound(matches.begin(), matches.end(), limit);
    // count number of primes
    auto result = std::distance(matches.begin(), lower);
    std::cout << result << std::endl;
  }

  return 0;
}