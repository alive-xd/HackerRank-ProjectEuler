#include <iostream>

//#define ORIGINAL

// count divisors
unsigned long long numDivisors(unsigned long long n) {
  unsigned int result = 1;
  auto reduce = n;
  // trial division by all prime numbers
  // => I didn't precompute a sieve, therefore divide by 2 and all odd numbers
  for (unsigned long long divisor = 2; divisor <= reduce; divisor++) {
    // 2 is the only even prime number
    if (divisor % 2 == 0 && divisor > 2)
      divisor++;

    if (divisor > 100) // WARNING: unsafe speed optimization !
      break; // returns correct values for original problem but fails for some Hackerrank test cases

    unsigned int exponent = 0;
    while (reduce % divisor == 0) {
      exponent++;
      reduce /= divisor;
    }

    result *= exponent + 1;
  }

  return result;
}

// count divisors of n^2, note: parameter is n, not n^2 (this is different from my old code in numDivisors)
unsigned long long numSquareDivisors(unsigned long long n) {
  unsigned int result = 1;
  auto reduce = n;
  // trial division by all prime numbers
  // => I didn't precompute a sieve, therefore divide by 2 and all odd numbers
  for (unsigned long long divisor = 2; divisor <= reduce; divisor++) {
    // 2 is the only even prime number
    if (divisor % 2 == 0 && divisor > 2)
      divisor++;

    unsigned int exponent = 0;
    while (reduce % divisor == 0) {
      exponent++;
      reduce /= divisor;
    }

    result *= 2 * exponent + 1; // changed vs. my code: times 2
  }

  return result;
}

int main() {

  unsigned int tests;
  std::cin >> tests;
  while (tests--) {
    // find the number of solutions
    unsigned long long n;
    std::cin >> n;

    auto divisors = numSquareDivisors(n);

    // a and b are interchangeable therefore only half of the solutions are "unique"
    auto half = (divisors + 1) / 2; // plus 1 because n^2 is obviously a square number
    std::cout << half << std::endl;
  }

  return 0;
}

// my initial brute force solution
int bruteForce(unsigned int threshold) {
  unsigned long long n = 4;
  while (true) {
    unsigned int solutions = 0;

    // try all values between n+1 ... 2n
    for (unsigned long long x = n + 1; x <= 2 * n; x++) {
      // the same as 1/x + 1/y = 1/n
      auto y = n * x / (x - n);
      // integer arithmetic might produce a wrong result, re-compute the formula backwards
      if (y * (x - n) != n * x)
        continue;

      // exhausted ?
      if (y < x)
        break;

      // valid solution
      solutions++;
    }

    if (solutions > threshold)
      break;

    n++;
  }

  std::cout << n << std::endl;
  return 0;
}