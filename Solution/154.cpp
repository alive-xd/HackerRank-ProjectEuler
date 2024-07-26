#include <iostream>
#include <vector>

typedef std::vector < unsigned int > Exponents;

// return exponent of a prime factor of C(n,k)
// looks a bit like the logarithm:
// C(n,k) = n! / ((n-k)! * k!)
unsigned int choose(const Exponents & sums, unsigned int n, unsigned int k) {
  return sums[n] - (sums[n - k] + sums[k]);
}

int main() {
  unsigned int layer = 200000;
  // 10^12 = 2^12 * 5^12
  unsigned int prime1 = 2;
  unsigned int exponent1 = 12;
  unsigned int prime2 = 5;
  unsigned int exponent2 = 12;
  std::cin >> layer >> prime1 >> exponent1 >> prime2 >> exponent2;

  // analyze for each number between 0 and layer how often they contain prime1 and prime2
  Exponents mulPrime1 = {
    0
  };
  Exponents mulPrime2 = {
    0
  };
  for (unsigned int x = 1; x <= layer; x++) {
    auto current = x;
    unsigned int count = 0;
    // extract first prime (=2) as often as possible
    while (current % prime1 == 0) {
      current /= prime1;
      count++;
    }
    mulPrime1.push_back(count);

    count = 0;
    // extract second prime (=5) as often as possible
    while (current % prime2 == 0) {
      current /= prime2;
      count++;
    }
    mulPrime2.push_back(count);
  }

  // sum1[x] = sum of mulPrime1[0 ... x]
  Exponents sum1;
  unsigned int count = 0;
  for (auto x: mulPrime1) {
    count += x;
    sum1.push_back(count);
  }

  // the same stuff for the other prime
  Exponents sum2;
  count = 0;
  for (auto x: mulPrime2) {
    count += x;
    sum2.push_back(count);
  }

  unsigned long long result = 0;
  for (unsigned int i = 0; i <= layer; i++) {
    // how often is each prime used by C(layer, i) ?
    auto found1 = choose(sum1, layer, i);
    auto found2 = choose(sum2, layer, i);

    // already enough ?
    if (found1 >= exponent1 && found2 >= exponent2) {
      // no need to enter the inner-most loop, each iteration would succeed
      result += i + 1;
      continue;
    }

    // note: abort early because of mirrored values
    for (unsigned int j = 0; j <= (i + 1) / 2; j++) {
      if (found1 + choose(sum1, i, j) >= exponent1 &&
        found2 + choose(sum2, i, j) >= exponent2) {
        // found a match
        result++;
        // left and right side are identical
        if (j < i / 2)
          result++;
      }
    }
  }

  // and we're done !
  std::cout << result << std::endl;
  return 0;
}