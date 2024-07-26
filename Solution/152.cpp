#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>

// uncomment to get more debugging output
//#define VERBOSE

// ---------- code copied from my toolbox ----------
// (I removed unused features to reduce source code size)

// simple class to representation a fraction
// note: no checks for a zero denominator
//       signs are not normalized
struct Fraction {
  // change to long long if you need to support larger values
  typedef unsigned __int128 T;

  // numerator
  T num;
  // denominator
  T den;

  Fraction(T numerator = 0, T denominator = 1): num(numerator), den(denominator) {}

  // add
  Fraction operator + (const Fraction & other) const {
    if (den == other.den)
      return Fraction(num + other.num, den);
    // n1/d1 + n2/d2 = (n1*d2 + n2*d1) / d1*d2
    return {
      num * other.den + other.num * den,
      den * other.den
    };
  }
  // subtract
  Fraction operator - (const Fraction & other) const {
    if (den == other.den)
      return Fraction(num - other.num, den);
    // n1/d1 - n2/d2 = (n1*d2 - n2*d1) / d1*d2
    return {
      num * other.den - other.num * den,
      den * other.den
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

  // convert to a proper fraction
  Fraction reduced() const {
    // catch simple cases: 0/d and n/1
    if (num == 0 || den == 1)
      return {
        num,
        1
      };

    // divide numerator and denominator by their gcd()
    // code taken from my toolbox / gcd()
    auto a = num;
    auto b = den;
    while (a != 0) {
      auto c = a;
      a = b % a;
      b = c;
    }
    // now b contains the gcd()
    if (b == 1)
      return *this;
    return {
      num / b,
      den / b
    };
  }
};

// ---------- problem-specific code ----------

// sum of fractions should be exactly 1/2
Fraction sum(1, 2);

// all fractions that could be used
std::vector < unsigned int > candidates;
// store all combinations of all fractions beyond 1/threshold^2
unsigned int lastNumberThreshold = 40;
std::multiset < Fraction > lastNumbers; // a simple std::set would suffice for limit = 80 and lastNumberThreshold = 40
// sum of all fractions whose denominator exceeds a value (e.g. 40 => all fractions 1/40^2 + 1/42^2 + ... 1/80^2)
std::map < unsigned int, Fraction > remaining; // is equal to the largest key in lastNumbers

// track fractions of the current sum (debugging only)
std::vector < unsigned char > members;

// count how many combinations add up to 1/2
unsigned int search(Fraction current = Fraction(0, 1), size_t next = 0) {
  // match !
  if (current == sum) {
    #ifdef VERBOSE
    for (auto x: members)
      std::cout << int(x) << " + ";
    std::cout << std::endl;
    #endif
    return 1;
  }

  // sum already too high ?
  if (sum < current)
    return 0;
  // no more terms ?
  if (next == candidates.size())
    return 0;

  // get next denominator (actually the whole fraction will be 1/number^2)
  auto number = candidates[next];

  // even if I choose all remaining number will it be enough to "reach" 1/2 ?
  auto maximum = current + remaining[number];
  if (maximum < sum)
    return 0;

  // lookup difference in all pre-computed sums of the last values
  if (number >= lastNumberThreshold) {
    // is there any sum matching the difference ?
    auto difference = sum - current;
    auto solutions = lastNumbers.count(difference);

    #ifdef VERBOSE
    if (solutions > 0) {
      for (auto x: members)
        std::cout << int(x) << " + ";
      std::cout << " (" << solutions << " solutions)" << std::endl;
    }
    #endif

    return solutions;
  }

  // keep searching ...
  unsigned long long result = 0;
  // try to build the sum without number
  result += search(current, next + 1);

  // try to build the sum with    number
  Fraction add(1, number * number);
  members.push_back(number);
  current = current + add;
  current = current.reduced();
  result += search(current, next + 1);
  members.pop_back();

  return result;
}

int main() {
  unsigned int denominator = 2;
  unsigned int limit = 80;
  std::cin >> denominator >> limit;
  sum.den = denominator;

  // find primes 2..80
  std::vector < unsigned int > primes;
  for (unsigned int i = 2; i <= limit; i++) {
    // basic trial division
    bool isPrime = true;
    for (unsigned int j = 2; j * j <= i; j++)
      if (i % j == 0) {
        isPrime = false;
        break;
      }
    if (isPrime)
      primes.push_back(i);
  }

  // determine relevant numbers
  std::set < unsigned int > relevantPrime;
  std::vector < bool > found(limit + 1, false);
  for (auto p: primes) {
    // enumarate 1/p^2, 1/(2p)^2, 1/(3p)^2, ...
    std::vector < Fraction > multiples;
    for (unsigned int m = p; m <= limit; m += p)
      multiples.push_back({
        1,
        m * m
      });

    // now check whether any combination is able to get rid of the prime in the denominator

    // go through all 2^n subsets
    auto combinations = 1 << multiples.size();
    for (auto mask = 1; mask < combinations; mask++) {
      // add all fractions
      Fraction current(0, 1);
      for (unsigned int pos = 0; pos < multiples.size(); pos++) {
        auto bit = 1 << pos;
        if ((bit & mask) == 0)
          continue;
        current = current + multiples[pos];
        current = current.reduced();
      }
      // and reduce them to a proper fraction
      current = current.reduced();

      // prime still there ? try another combination ...
      if (current.den % p == 0)
        continue;

      // same loop again, now mark all involved numbers as "found"
      for (unsigned int pos = 0; pos < multiples.size(); pos++) {
        auto bit = 1 << pos;
        if ((bit & mask) == 0)
          continue;

        // p is at position 0, 2p at 1, 3p at 2, ...
        auto isGood = (pos + 1) * p;
        found[isGood] = true;
      }

      // yes, it's a relevant prime
      relevantPrime.insert(p);
      found[p] = true;

      // analyze all combinations only for p >= 5 (special treatment for p=2 and p=3 follows below)
      if (p < 5)
        break;
    }
  }

  // assume that all numbers 2^n * 3^m need to be considered
  // (I only have to do this because the previous loop would be waaaay to slow for full evaluation of all cases)
  for (unsigned int two = 1; two <= limit; two *= 2)
    for (unsigned int three = 1; two * three <= limit; three *= 3)
      found[two * three] = true;

  // each suitable number between 2..80 must only consist of relevant primes
  for (unsigned int i = 2; i <= limit; i++) {
    // I don't need this number ?
    if (!found[i])
      continue;

    // factorize
    auto reduce = i;
    for (auto p: relevantPrime)
      while (reduce % p == 0)
        reduce /= p;

    if (reduce != 1) {
      found[i] = false;
      continue;
    }

    // yes, all prime factors found in relevantPrimes
    candidates.push_back(i);
  }

  // my code finds 2,3,4,5,6,7,8,9,10,12,13,14,15,16,18,20,21,24,27,28,30,32,35,36,39,40,42,45,48,52,54,56,60,63,64,65,70,72,80
  // but I analyzed all valid sums and found that only these numbers are actually needed:
  //candidates = { 2,3,4,5,6,7,8,9,10,12,13,14,15,   18,20,21,24,   28,30,   35,36,39,40,42,45,   52,   56,60,63,      70,72 };

  #ifdef VERBOSE
  for (auto x: candidates)
    std::cout << x << ",";
  std::cout << std::endl;
  #endif

  // for each number n compute the sum of 1/n^2 from n to 80
  // e.g. then I know for n = 9 whether I can reach 1/2 (or more) if I would use all remaining fractions
  // => it becomes obvious that I always need 2
  // => and I need 3 or 4
  // => helps me to skip analyzed many cases where the sum is just too small
  Fraction sum(0, 1);
  for (auto i = candidates.rbegin(); i != candidates.rend(); i++) {
    auto current = * i;
    sum = sum + Fraction(1, current * current);
    sum = sum.reduced();
    remaining[current] = sum;
  }

  // precompute sums of all combinations of the last numbers
  lastNumberThreshold = limit / 2; // arbitrary heuristic: all relevant numbers >= 40
  // it just turned out to be the fastest/best threshold ...
  // get range of the last numbers
  auto iteLastNumbers = candidates.begin();
  while (iteLastNumbers != candidates.end() && * iteLastNumbers < lastNumberThreshold)
    iteLastNumbers++;
  auto numLastNumbers = std::distance(iteLastNumbers, candidates.end());

  // go through all 2^numLastNumbers combinations
  unsigned int combinations = 1 << numLastNumbers;
  for (unsigned int i = 0; i < combinations; i++) {
    // add all fractions for each subset
    Fraction current(0, 1);
    for (unsigned int pos = 0; pos < numLastNumbers; pos++) {
      auto bit = 1 << pos;
      if ((i & bit) == 0)
        continue;

      auto add = * (iteLastNumbers + pos);
      current = current + Fraction(1, add * add);
      current = current.reduced();
    }
    // store for later use in search()
    lastNumbers.insert(current);
  }

  // let's go !
  std::cout << search() << std::endl;
  return 0;
}