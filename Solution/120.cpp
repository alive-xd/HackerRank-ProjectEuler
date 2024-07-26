
#include <iostream>


#include <deque>

// return (a*b) % modulo
unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long modulo)
{
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
  while (a > 0 && b > 0)
  {
    // b is odd ? a*b = a + a*(b-1)
    if (b & 1)
    {
      result += a;
      result %= modulo;
      // skip b-- because the bit-shift at the end will remove the lowest bit anyway
    }

    // b is even ? a*b = (2*a)*(b/2)
    a <<= 1;
    a  %= modulo;

    // next bit
    b >>= 1;
  }

  return result;
}

// return (base^exponent) % modulo
unsigned long long powmod(unsigned long long base, unsigned long long exponent, unsigned long long modulo)
{
  unsigned long long result = 1;
  while (exponent > 0)
  {
    // fast exponentation:
    // odd exponent ? a^b = a*a^(b-1)
    if (exponent & 1)
      result = mulmod(result, base, modulo);

    // even exponent ? a^b = (a*a)^(b/2)
    base = mulmod(base, base, modulo);
    exponent >>= 1;
  }
  return result;
}

int main()
{
  const unsigned int minA   = 1;
  const unsigned int Modulo = 1000000007;

  std::deque<unsigned int> sums2(minA, 0);
  std::deque<unsigned int> sums3(minA, 0);

  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--)
  {
    unsigned int exponent = 2;
    unsigned long long maxA = 1000;
    std::cin >> maxA >> exponent;

    unsigned long long sum = 0;
    if (exponent == 2)
    {
      // closed formula
      {
        unsigned __int128 half = maxA / 2;
        sum  = half * (8*half*half - 3*half - 5) / 3;

        if (maxA % 2 == 1)
          sum += (maxA*maxA -   maxA) % Modulo;

        sum += 2; // maxA == 1
        sum %= Modulo;
        std::cout << sum << std::endl;
        continue;
      }

      sum = sums2.back();
      for (auto a = sums2.size(); a <= maxA; a++)
      {
        unsigned long long A = a; // make sure that a*a is computed in  64 bit to avoid overflows
        unsigned int even = (A*A - 2*A) % Modulo;
        unsigned int odd  = (A*A -   A) % Modulo;

        // direct evaluation
        if (a == 1) // the formulas below fail for a == 1 ...
          sum += 2;
        else if (a % 2 == 0)
          sum += even; // for even numbers
        else
          sum += odd;  // for odd  numbers

        sum %= Modulo;
        sums2.push_back(sum);
      }

      sum = sums2[maxA];
    }
    else // exponent = 3
    {
      sum = sums3.back();
      for (auto a = sums3.size(); a <= maxA; a++)
      {
        unsigned __int128 A = a; // make sure that a*a*a is computed in 128 bit to avoid overflows
        unsigned int even = (A*A*A - 2*A) % Modulo;
        unsigned int odd  = (A*A*A -   A) % Modulo;

        if (a == 1) // the formulas below fail for a == 1 ...
          sum += 0;
        else if (a % 2 == 0)
          sum += even; // for even numbers
        else
          sum += odd;  // for odd  numbers

        sum %= Modulo;
        sums3.push_back(sum);
      }

      sum = sums3[maxA];
    }

    // print result
    std::cout << sum << std::endl;
  }

  return 0;
}

