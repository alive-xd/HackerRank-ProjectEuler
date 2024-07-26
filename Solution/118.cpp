
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


/////////////// prime sieve ///////////////
// odd prime numbers are marked as "true" in a bitvector
std::vector<bool> sieve;
// return true, if x is a prime number
bool isPrime(unsigned int x)
{
  // handle even numbers
  if ((x & 1) == 0)
    return x == 2;

  // trial division for large numbers
  if (x >= sieve.size() * 2)
  {
    for (unsigned int i = 3; i*i <= x; i += 2)
      if (x % i == 0)
        return false;
    return true;
  }

  // lookup for odd numbers
  return sieve[x >> 1];
}

// find all prime numbers from 2 to size
void fillSieve(unsigned int size)
{
  // store only odd numbers
  const unsigned int half = size >> 1;

  // allocate memory
  sieve.resize(half, true);
  // 1 is not a prime number
  sieve[0] = false;

  // process all relevant prime factors
  for (unsigned int i = 1; 2 * i*i < half; i++)
    // do we have a prime factor ?
    if (sieve[i])
    {
      // mark all its multiples as false
      unsigned int current = 3 * i + 1;
      while (current < half)
      {
        sieve[current] = false;
        current += 2 * i + 1;
      }
    }
}


/////////////// solution ///////////////
typedef std::vector<unsigned int> Digits;
std::vector<std::vector<unsigned int>> solutions;
void search(const Digits& digits, std::vector<unsigned int>& merged, size_t firstPos = 0)
{
  // no more digits left => found a solution
  if (firstPos == digits.size())
  {
    solutions.push_back(merged);
    return;
  }

  // process one more digit at a time
  unsigned int current = 0;
  while (firstPos < digits.size())
  {
    // next digit
    current *= 10;
    current += digits[firstPos++];

    // must be larger than its predecessor
    if (!merged.empty() && current < merged.back())
      continue;

    // ... and prime, of course !
    if (isPrime(current))
    {
      merged.push_back(current);
      search(digits, merged, firstPos);
      merged.pop_back();
    }
  }
}

int main()
{
  // precompute primes (bigger primes are tested using trial division)
  fillSieve(100000000);

  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--)
  {
    // read digits
    std::string strDigits = "123456789";
    std::cin >> strDigits;

    // convert to a sorted array/vector
    Digits digits;
    for (auto x : strDigits)
      digits.push_back(x - '0');
    std::sort(digits.begin(), digits.end());

    // discard solutions from previous tests
    solutions.clear();
    do
    {
      // simple speed optimization: last digit must be odd (or it's 2)
      if (digits.back() % 2 == 0 && (digits.size() > 1 || digits.back() != 2))
        continue;

      // let's go !
      std::vector<unsigned int> merged;
      search(digits, merged);
    } while (std::next_permutation(digits.begin(), digits.end()));

    // compute sum of each solution
    std::vector<unsigned long long> sorted;
    for (auto merged : solutions)
    {
      unsigned long long sum = 0;
      for (auto x : merged)
        sum += x;
      sorted.push_back(sum);
    }
    // sort ascendingly
    std::sort(sorted.begin(), sorted.end());

    // remove duplicates (needed ?)
    //auto garbage = std::unique(sorted.begin(), sorted.end());
    //sorted.erase(garbage, sorted.end());

    // and print all of them
    for (auto x : sorted)
      std::cout << x << std::endl;
    std::cout << std::endl;

  }

  return 0;
}
