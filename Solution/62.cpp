#include <map>
#include <set>
#include <vector>
#include <iostream>

// count how often each digit occurs,
// store zero at lowest position, then ones, etc.
// e.g. 5063 means 3 zeros, 6 ones, no twos, 5 threes and nothing else
// note: can't handle input values with 2^6 or more identical digits
unsigned long long fingerprint(unsigned long long x) {
  unsigned long long result = 0;
  while (x > 0) {
    // extract lowest digit
    auto digit = x % 10;
    x /= 10;

    // subdivide 64 bit integer into 10 "digit counters", each 6 bits wide
    // => each digit may occur up to 2^6=64 times, more than enough ...
    const auto BitsPerDigit = 6;
    result += 1ULL << (BitsPerDigit * digit);
  }
  return result;
}

int main() {
  unsigned int maxCube = 10000;
  unsigned int numPermutations = 5;
  std::cin >> maxCube >> numPermutations;

  // [fingerprint] => [list of numbers, where number^3 produced that fingerprint]
  std::map < unsigned long long, std::vector < unsigned int >> matches;
  for (unsigned int i = 1; i < maxCube; i++) {
    // find fingerprint
    auto cube = (unsigned long long) i * i * i;
    // add current number to the fingerprint's list
    matches[fingerprint(cube)].push_back(i);
  }

  // extract all smallest cube, std::set is sorting them
  std::set < unsigned long long > smallest;
  for (auto m: matches)
    // right number of permutations ?
    if (m.second.size() == numPermutations)
      smallest.insert(m.second.front());

  // print in ascending order
  for (auto s: smallest)
    std::cout << (s * s * s) << std::endl;

  return 0;
}