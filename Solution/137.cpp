#include <iostream>

// return (a*b) % modulo
unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long modulo) {
  // (a * b) % modulo = (a % modulo) * (b % modulo) % modulo
  a %= modulo;
  b %= modulo;

  // fast path
  if (a <= 0xFFFFFFF && b <= 0xFFFFFFF)
    return (a * b) % modulo;

  // we might encounter overflows (slow path)
  // the number of loops depends on b, therefore try to minimize b
  if (b > a)
    std::swap(a, b);

  // bitwise multiplication
  unsigned long long result = 0;
  while (a > 0 && b > 0) {
    // b is odd ? a*b = a + a*(b-1)
    if (b & 1) {
      result += a;
      if (result >= modulo)
        result -= modulo;
      // skip b-- because the bit-shift at the end will remove the lowest bit anyway
    }

    // b is even ? a*b = (2*a)*(b/2)
    a <<= 1;
    if (a >= modulo)
      a -= modulo;

    // next bit
    b >>= 1;
  }

  return result;
}

// Fibonacci matrix algorithm (taken from my solution of problem 304)
// return (Fibonacci(2n) * Fibonacci(2n+1)) % modulo
unsigned long long nugget(unsigned long long n, unsigned long long modulo) {
  // n-th nugget is based on Fibonacci(2n) and Fibonacci(2n+1)
  n *= 2;

  // fast exponentiation: same idea as powmod from my toolbox

  // matrix values from https://en.wikipedia.org/wiki/Fibonacci_number#Matrix_form
  unsigned long long fibo[2][2] = {
    {
      1,
      1
    },
    {
      1,
      0
    }
  };
  // initially identity matrix
  unsigned long long result[2][2] = {
    {
      1,
      0
    }, // { { F(n+1), F(n)   },
    {
      0,
      1
    }
  }; //   { F(n),   F(n-1) } }

  while (n > 0) {
    // fast exponentation:
    // odd exponent ? a^n = a*a^(n-1)
    if (n & 1) {
      // compute new values, store them in temporaries
      auto t00 = mulmod(result[0][0], fibo[0][0], modulo) + mulmod(result[0][1], fibo[1][0], modulo);
      auto t01 = mulmod(result[0][0], fibo[0][1], modulo) + mulmod(result[0][1], fibo[1][1], modulo);
      auto t10 = mulmod(result[1][0], fibo[0][0], modulo) + mulmod(result[1][1], fibo[1][0], modulo);
      auto t11 = mulmod(result[1][0], fibo[0][1], modulo) + mulmod(result[1][1], fibo[1][1], modulo);

      if (t00 >= modulo) t00 -= modulo;
      if (t01 >= modulo) t01 -= modulo;
      if (t10 >= modulo) t10 -= modulo;
      if (t11 >= modulo) t11 -= modulo;

      // copy back to matrix
      result[0][0] = t00;
      result[0][1] = t01;
      result[1][0] = t10;
      result[1][1] = t11;
    }

    // even exponent ? a^n = (a*a)^(n/2)

    // compute new values, store them in temporaries
    auto t00 = mulmod(fibo[0][0], fibo[0][0], modulo) + mulmod(fibo[0][1], fibo[1][0], modulo);
    auto t01 = mulmod(fibo[0][0], fibo[0][1], modulo) + mulmod(fibo[0][1], fibo[1][1], modulo);
    auto t10 = mulmod(fibo[1][0], fibo[0][0], modulo) + mulmod(fibo[1][1], fibo[1][0], modulo);
    auto t11 = mulmod(fibo[1][0], fibo[0][1], modulo) + mulmod(fibo[1][1], fibo[1][1], modulo);

    if (t00 >= modulo) t00 -= modulo;
    if (t01 >= modulo) t01 -= modulo;
    if (t10 >= modulo) t10 -= modulo;
    if (t11 >= modulo) t11 -= modulo;

    // copy back to matrix
    fibo[0][0] = t00;
    fibo[0][1] = t01;
    fibo[1][0] = t10;
    fibo[1][1] = t11;

    n >>= 1;
  }

  // F(2n + 1) * F(2n)
  return (result[0][0] * result[0][1]) % modulo;
}

int main() {
  // 10^9 + 7
  const unsigned long long Modulo = 1000000007;

  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--) {
    unsigned long long n;
    std::cin >> n;
    std::cout << nugget(n, Modulo) << std::endl;
  }
  return 0;
}