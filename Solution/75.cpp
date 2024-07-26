#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

template < typename T >
  T gcd(T x, T y) {
    while (x != 0) {
      T t = x;
      x = y % x;
      y = t;
    }
    return y;
  }

int main() {
  const unsigned int max_len = 5 * 1000 * 1000;

  std::vector < unsigned int > comb(max_len, 0);

  for (unsigned int i = 2; i < sqrt(max_len); i++) {
    for (unsigned int j = 1; j < i; j++) {
      if ((i + j) % 2 != 1) {
        continue;
      }
      if (gcd(i, j) != 1) {
        continue;
      }

      auto x = i * i - j * j;
      auto y = 2 * i * j;
      auto z = i * i + j * j;
      auto sum = x + y + z;

      unsigned int k = 1;
      while (k * sum <= max_len) {
        comb[k * sum]++;
        k++;
      }
    }
  }

  std::vector < unsigned int > once;

  for (size_t i = 0; i < comb.size(); i++) {
    if (comb[i] == 1) {
      once.push_back(i);
    }
  }

  unsigned int t = 1;
  std::cin >> t;
  while (t--) {
    unsigned int limit = 1500000;
    std::cin >> limit;

    auto pos = std::upper_bound(once.begin(), once.end(), limit);
    auto res = std::distance(once.begin(), pos);
    std::cout << res << std::endl;
  }
}