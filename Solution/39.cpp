#include <iostream>
#include <set>
#include <vector>

// greatest common divisor
unsigned int gcd(unsigned int a, unsigned int b) {
  while (a != 0) {
    unsigned int c = a;
    a = b % a;
    b = c;
  }
  return b;
}

int main() {
  const unsigned int MaxPerimeter = 5000000;

  // precomputation step 1:
  // count all triplets per perimeter (up to upper limit 5 * 10^6)
  // [perimeter] => [number of triplets]
  std::vector < unsigned int > count(MaxPerimeter + 1, 0);

  // note: long long instead of int because otherwise the squares m^2, n^2, ... might overflow
  for (unsigned long long m = 1; 2 * m * m < MaxPerimeter; m++)
    for (unsigned long long n = 1; n < m; n++) {
      // make sure all triplets a,b,c are unique
      if (m % 2 == 1 && n % 2 == 1)
        continue;
      if (gcd(m, n) > 1)
        continue;

      unsigned int k = 1;
      while (true) {
        // see Euclidian formula above
        auto a = k * (m * m - n * n);
        auto b = k * 2 * m * n;
        auto c = k * (m * m + n * n);
        k++;

        // abort if largest perimeter is exceeded
        auto perimeter = a + b + c;
        if (perimeter > MaxPerimeter)
          break;

        // ok, found a triplet
        count[perimeter]++;
      }
    }

  // precomputation step 2:
  // store only best perimeters
  unsigned long long bestCount = 0;
  std::set < unsigned int > best;
  best.insert(0); // degenerated case
  for (unsigned int i = 0; i < count.size(); i++)
    if (bestCount < count[i]) {
      bestCount = count[i];
      best.insert(i);
    }

  // processing input boils down to a simple lookup
  unsigned int tests;
  std::cin >> tests;
  while (tests--) {
    unsigned int maxPerimeter;
    std::cin >> maxPerimeter;

    // find the perimeter with the largest count
    auto i = best.upper_bound(maxPerimeter);
    // we went one step too far
    i--;
    // print result
    std::cout << * i << std::endl;
  }
  return 0;
}