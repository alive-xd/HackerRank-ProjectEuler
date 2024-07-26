
#include <iostream>
#include <vector>
#include <algorithm>

// store a single radical
struct Radical
{
  // current number
  unsigned int n;
  // product of all prime factors
  unsigned int product;

  // compare two object, prefer lower product (and lower n if products are equal)
  bool operator<(const Radical& other) const
  {
    if (product != other.product)
      return product < other.product;
    return n < other.n;
  }
};

// all relevant redicals
std::vector<Radical> rads;

// return a certain radical (1-based index)
unsigned int getNth(unsigned int index)
{
  index--; // 1-based instead of 0-based
  // partial sort
  std::nth_element(rads.begin(), rads.begin() + index, rads.end());
  return rads[index].n;
}

int main()
{
  unsigned int tests;
  std::cin >> tests;
  while (tests--)
  {
    unsigned int limit = 100000;
    std::cin >> limit;

    // initialize all radicals
    rads.clear();
    rads.reserve(limit + 1);
    for (unsigned int i = 0; i <= limit; i++)
    {
      Radical current;
      current.n = i;
      current.product = 1;
      rads.push_back(current);
    }

    // some big value to push zero to the back
    rads[0].product = 999999999;

    // compute radicals using a "sieve"
    for (auto current : rads)
    {
      // process only primes
      if (current.product != 1)
        continue;

      // adjust all of their multiples
      for (unsigned int j = current.n; j <= limit; j += current.n)
        rads[j].product *= current.n;
    }

    // get n-th element
    unsigned int pos = 10000;
    std::cin >> pos;
    std::cout << getNth(pos) << std::endl;
  }
  return 0;
}
