#include <iostream>
#include <vector>
#include <cmath>

// ---------- standard prime sieve from my toolbox ----------
// note: a small tweak: fillSieve() aborts if sieve[] already has enough values

// odd prime numbers are marked as "true" in a bitvector
std::vector < bool > sieve;

// return true, if x is a prime number
bool isPrime(unsigned int x) {
  // handle even numbers
  if ((x & 1) == 0)
    return x == 2;

  // lookup for odd numbers
  return sieve[x >> 1];
}

// find all prime numbers from 2 to size
void fillSieve(unsigned int size) {
  // store only odd numbers
  const unsigned int half = (size >> 1) + 1;

  // already existing ?
  if (sieve.size() >= half)
    return;

  // allocate memory
  sieve.resize(half, true);
  // 1 is not a prime number
  sieve[0] = false;

  // process all relevant prime factors
  for (unsigned int i = 1; 2 * i * i < half; i++)
    // do we have a prime factor ?
    if (sieve[i]) {
      // mark all its multiples as false
      unsigned int current = 3 * i + 1;
      while (current < half) {
        sieve[current] = false;
        current += 2 * i + 1;
      }
    }
}

// ---------- now problem-specific code ----------

// return number at position (x, y) where x <= y
unsigned long long getNumber(unsigned int x, unsigned int y) {
  // the last number in a line is a triangle number
  // return x + T(y-1)
  return x + y * (y - 1ULL) / 2;
}

std::vector < bool > segment;
unsigned long long segmentStart = 0;
// set segment[x] to true if x+from is prime
void fillSegmentedSieve(unsigned long long from, unsigned long long to) {
  // plain old sieve for all primes up to sqrt(to)
  fillSieve(sqrt(to));

  // first number covered by the segment
  segmentStart = from | 1; // start with an odd number
  // size of the segment
  auto numValues = to - from + 1;

  // assume all numbers are prime
  segment.clear();
  segment.resize(numValues + 1, true);

  // cross off composites
  for (unsigned long long p = 3; p * p <= to; p += 2)
    if (isPrime(p)) {
      // find smallest multiple in the segment
      auto smallest = from - (from % p) + p;
      // only odd multiples
      if (smallest % 2 == 0)
        smallest += p;
      // walk through all odd multiples
      for (size_t i = smallest; i <= to; i += 2 * p)
        segment[(i - segmentStart) / 2] = false;
    }
}

// return true if number at position (x,y) is prime
// check boundaries, too (there parameter x can be negative)
bool isPrimeInSegment(int x, int y) {
  // out of bounds ?
  if (x < 1 || x > y)
    return false;

  // check segmented sieve at that position
  auto current = getNumber(x, y);
  // reject all even number (except 2)
  if (current % 2 == 0)
    return current == 2;

  // luokup
  return segment[(current - segmentStart) / 2];
}

// return sum of all prime triplets in a certain line
unsigned long long processLine(unsigned int line) {
  // need to look two lines up and down
  auto sieveFrom = getNumber(1, line - 2);
  auto sieveTo = getNumber(1, line + 3) - 1;

  // prevent line - 2 from becoming negative and producing strange results
  if (line <= 2)
    sieveFrom = 1;

  // find all primes numbers for those 5 lines
  fillSegmentedSieve(sieveFrom, sieveTo);

  // find all primes with at least two direct neighbors that are prime, too
  std::vector < bool > threePlus(segment.size(), false);
  for (unsigned int y = line - 1; y <= line + 1; y++)
    for (unsigned int x = 1; x <= y; x++) {
      // current number must be a prime
      if (!isPrimeInSegment(x, y))
        continue;

      // count all primes in the 3x3 neighborhood (one step up,up-right,right,down-right,down, ...)
      auto countPrimes = 0; // actually countPrimes is always at least 1 because there must be a prime at deltaX = deltaY = 0
      for (int deltaX = -1; deltaX <= +1; deltaX++)
        for (int deltaY = -1; deltaY <= +1; deltaY++)
          if (countPrimes < 3 && isPrimeInSegment(x + deltaX, y + deltaY))
            countPrimes++;

      // at least three primes ?
      threePlus[getNumber(x, y) - segmentStart] = (countPrimes >= 3);
    }

  // now look at the current line and compute sum of all triplets
  unsigned long long sum = 0;
  for (unsigned int x = 1; x <= line; x++) {
    // current number must be a prime
    auto current = getNumber(x, line);
    if (!isPrimeInSegment(x, line))
      continue;

    // look at 3x3 neighborhood whether at least one cell has threePlus[] = true
    bool atLeastThree = false;
    for (int deltaX = -1; deltaX <= +1; deltaX++)
      for (int deltaY = -1; deltaY <= +1; deltaY++)
        atLeastThree |= threePlus[getNumber(x + deltaX, line + deltaY) - segmentStart];

    // found a triplet ?
    if (atLeastThree)
      sum += current;
  }

  return sum;
}

int main() {
  unsigned int one = 5678027;
  unsigned int two = 7208785;
  std::cin >> one >> two;

  // fillSieve can re-use existing data if the second number not bigger than the first
  if (one < two)
    std::swap(one, two);

  std::cout << processLine(one) + processLine(two) << std::endl;
  return 0;
}