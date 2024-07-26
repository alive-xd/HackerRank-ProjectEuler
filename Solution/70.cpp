#include <iostream>
#include <vector>

// precompute all primes less than sqrt(10^7)
std::vector < unsigned int > primes;

// return phi(x) if x/phi(x) <= minQuotient (else the result is undefined but > minQuotient)
unsigned int phi(unsigned int x, double minQuotient) {
  // totient function can be computed by finding all prime factors p
  // and subtracting them from x
  auto result = x;
  auto reduced = x;
  for (auto p: primes) {
    // prime factors have to be p <= sqrt
    if (p * p > reduced)
      break;

    // not a prime factor ...
    if (reduced % p != 0)
      continue;

    // prime factors may occur multiple times, remove them all
    do {
      reduced /= p;
    } while (reduced % p == 0);

    // but subtract from result only once
    result -= result / p;

    // abort, this number can't be relevant because the quotient is already too high
    if (result * minQuotient < x)
      return result; // number is garbage but always >= its correct value
  }

  // prime number (result is still equal to x because we couldn't find any prime factors)
  if (result == x)
    return x - 1;
  // (actually this case would be properly handled by the next if-clause, too)

  // we only checked prime factors <= sqrt(x)
  // there might exist one (!) prime factor > sqrt(x)
  // e.g. 3 is a prime factor of 6, and 3 > sqrt(6)
  if (reduced > 1)
    return result - result / reduced;
  else
    return result;
}

// count digits, two numbers have the same fingerprint if they are permutations of each other
unsigned long long fingerprint(unsigned int x) {
  unsigned long long result = 0;
  while (x > 0) {
    auto digit = x % 10;
    x /= 10;

    unsigned long long shift = 1;
    for (unsigned int i = 0; i < digit; i++)
      shift *= 10;

    result += shift;
  }
  return result;
}

int main() {
  unsigned int last;
  std::cin >> last;

  // step 1: the usual prime sieve
  primes.push_back(2);
  for (unsigned int i = 3; i * i < last; i += 2) {
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

    // yes, we have a prime number
    if (isPrime)
      primes.push_back(i);
  }

  // step 2: analyze all phi(n)
  unsigned int bestNumber = 2;
  double minQuotient = 999999;
  for (unsigned int n = 3; n < last; n++) {
    auto phi_n = phi(n, minQuotient);
    double quotient = n / double(phi_n);
    // already have a better quotient ?
    if (minQuotient <= quotient)
      continue;

    // check if phi(n) is a permutation of n
    if (fingerprint(phi_n) == fingerprint(n)) {
      minQuotient = quotient;
      bestNumber = n;
    }
  }

  // print result
  std::cout << bestNumber << std::endl;
  return 0;
}