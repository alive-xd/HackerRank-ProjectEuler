#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// use std::vector instead of std::set
#define FAST

// ---------- code from my toolbox ----------

// simple class to representation a fraction
// note: no checks for a zero denominator
//       signs are not normalized
struct Fraction {
  // change to long long if you need to support larger values
  typedef unsigned short T;

  // numerator
  T num;
  // denominator
  T den;

  Fraction(T numerator, T denominator = 1): num(numerator), den(denominator) {}

  // add
  Fraction operator + (const Fraction & other) const {
    // n1/d1 + n2/d2 = (n1*d2 + n2*d1) / d1*d2
    return {
      T(num * other.den + other.num * den),
      T(den * other.den)
    };
  }

  // sort
  bool operator < (const Fraction & other) const {
    // n1/d1 < n2/d2 => n1*d2 < n2*d2
    return num * other.den < other.num * den;
  }
  // compare
  bool operator == (const Fraction & other) const {
    // n1/d1 < n2/d2 => n1*d2 < n2*d2
    return num * other.den == other.num * den;
  }

  // return Fraction with swapped numerator and denominator
  Fraction inverse() const {
    return {
      den,
      num
    };
  }
};

// ---------- problem-specific code ----------

int main() {
  unsigned int limit = 18;
  std::cin >> limit;

  // capacitance of a single element (1 F)
  Fraction Capacitance = 1;

  // store all circuits
  #ifdef FAST
  std::vector < std::vector < Fraction >> circuits;
  #else
  std::vector < std::set < Fraction >> circuits;
  #endif
  circuits.resize(limit + 1);

  // only one basic circuit at level 1 (I use 1F instead of 60uF but the exact value is irrelevant)
  circuits[1] = {
    Capacitance
  };

  // find all circuits consisting of 2,3,4, ... 18 elements
  for (unsigned int sizeC = 2; sizeC <= limit; sizeC++) {
    // split into "sub-circuits" A and B where size(A) <= size(B)
    for (unsigned int sizeA = 1; sizeA <= sizeC / 2; sizeA++) {
      // remaining circuits
      auto sizeB = sizeC - sizeA;

      // create all combinations
      for (auto circuitA: circuits[sizeA])
        for (auto circuitB: circuits[sizeB]) {
          // serial connection
          // c = a + b
          auto serial = circuitA + circuitB;
          #ifdef FAST
          circuits[sizeC].push_back(serial);
          #else
          circuits[sizeC].insert(serial);
          #endif

          // parallel connection
          // 1/c = 1/a + 1/b
          // invC = invA + invB where invC = 1/c and invA = 1/a and invB = 1/b
          auto parallel = (circuitA.inverse() + circuitB.inverse()).inverse();
          #ifdef FAST
          circuits[sizeC].push_back(parallel);
          #else
          circuits[sizeC].insert(parallel);
          #endif
        }
    }

    #ifdef FAST
    // remove duplicates
    std::sort(circuits[sizeC].begin(), circuits[sizeC].end());
    auto garbage = std::unique(circuits[sizeC].begin(), circuits[sizeC].end());
    circuits[sizeC].erase(garbage, circuits[sizeC].end());
    #endif
  }

  // merge all circuits
  std::vector < Fraction > all;
  #ifdef FAST
  // little trick to keep memory usage low: move the largest vector's content instead of copying
  all = std::move(circuits[limit]);
  limit--;
  #endif
  // copy all capacitances
  for (unsigned int i = 1; i <= limit; i++)
    all.insert(all.end(), circuits[i].begin(), circuits[i].end());

  // and remove duplicates
  std::sort(all.begin(), all.end());
  auto garbage = std::unique(all.begin(), all.end());
  // count unique fractions
  auto numUnique = std::distance(all.begin(), garbage);
  std::cout << numUnique << std::endl;
  return 0;
}