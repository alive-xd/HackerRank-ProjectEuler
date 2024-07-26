#include <string>
#include <iostream>
#include <algorithm>

// true, if x contains only distinct digits
bool isPandigital(unsigned long long x) {
  unsigned char used[10] = {
    0
  };
  while (x > 0) {
    auto digit = x % 10;
    // digit already used ?
    if (used[digit] == 1)
      return false;
    used[digit]++;
    x /= 10;
  }

  return true;
}

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
  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--) {
    std::string current = "9876543210";
    std::cin >> current;

    // find next smaller pandigital number (only to avoid malicious input)
    unsigned long long adjusted = std::stoll(current);
    if (adjusted < 1023456789)
      adjusted = 1023456789;
    while (!isPandigital(adjusted))
      adjusted--;
    current = std::to_string(adjusted);

    // start search
    bool found = false;
    do {
      // split into two parts and check each common divisor
      for (size_t split = 1; split < current.size() && !found; split++) {
        // must not begin with a zero
        if (current[0] == '0' || current[split] == '0')
          continue;

        auto left = std::stoll(current.substr(0, split));
        auto right = std::stoll(current.substr(split));

        // any common divisors ?
        unsigned int shared = gcd(left, right);
        const unsigned int MultipleOfThree = 3; // I saw that all divisors are always multiples of three
        for (unsigned int factor = MultipleOfThree; factor <= shared; factor += MultipleOfThree) {
          // analyze all common divisors
          if (left % factor == 0 &&
            right % factor == 0) {
            // combine all digits
            unsigned int one = left / factor;
            unsigned int two = right / factor;
            std::string sequence = std::to_string(factor) +
              std::to_string(one) +
              std::to_string(two);

            // must have exactly 10 pandigital digits
            if (sequence.size() == 10 && isPandigital(std::stoll(sequence))) {
              found = true;
              std::cout << factor << "*(" << one << "," << two << ")=" << current << std::endl;
              break;
            }
          }
        }
      }

      // done ?
      if (found)
        break;
    } while (std::prev_permutation(current.begin(), current.end()));
  }

  return 0;
}