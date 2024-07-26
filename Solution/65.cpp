#include <iostream>
#include <vector>

// store single digits with lowest digits first
// e.g. 1024 is stored as { 4,2,0,1 }
// only non-negative numbers supported
struct BigNum: public std::vector < unsigned int > {
  // string conversion works only properly when MaxDigit is a power of 10
  static
  const unsigned int MaxDigit = 1000000000;

  // store a non-negative number
  BigNum(unsigned long long x = 0) {
    do {
      push_back(x % MaxDigit);
      x /= MaxDigit;
    } while (x > 0);
  }

  // add two big numbers
  BigNum operator + (const BigNum & other) const {
    auto result = * this;
    // add in-place, make sure it's big enough
    if (result.size() < other.size())
      result.resize(other.size(), 0);

    unsigned int carry = 0;
    for (size_t i = 0; i < result.size(); i++) {
      carry += result[i];
      if (i < other.size())
        carry += other[i];
      else
      if (carry == 0)
        return result;

      if (carry < MaxDigit) {
        // no overflow
        result[i] = carry;
        carry = 0;
      } else {
        // yes, we have an overflow
        result[i] = carry - MaxDigit;
        carry = 1;
      }
    }

    if (carry > 0)
      result.push_back(carry);

    return result;
  }

  // multiply a big number by an integer
  BigNum operator * (unsigned int factor) const {
    unsigned long long carry = 0;
    auto result = * this;
    for (auto & i: result) {
      carry += i * (unsigned long long) factor;
      i = carry % MaxDigit;
      carry /= MaxDigit;
    }
    // store remaining carry in new digits
    while (carry > 0) {
      result.push_back(carry % MaxDigit);
      carry /= MaxDigit;
    }

    return result;
  }
};

int main() {
  unsigned int lastIndex;
  std::cin >> lastIndex;

  // to save memory we dont keep all numerators, only the latest three
  BigNum numerators[3] = {
    0, // dummy, will be overwritten immediately
    1, // always 1
    2
  }; // the first number of the continuous fraction ("before the semicolon")

  for (unsigned int index = 2; index <= lastIndex; index++) {
    // e = [2; 1,2,1, 1,4,1, ... 1,2k,1, ...]
    unsigned int fractionNumber = 1;
    if (index % 3 == 0)
      fractionNumber = (index / 3) * 2;

    // keep only the latest two numerators
    numerators[0] = std::move(numerators[1]);
    numerators[1] = std::move(numerators[2]);
    // and generate the next one
    if (fractionNumber == 1)
      numerators[2] = numerators[0] + numerators[1];
    else
      numerators[2] = numerators[0] + numerators[1] * fractionNumber;
  }

  // add all digits of the last numerator
  unsigned int sum = 0;
  for (auto x: numerators[2])
    // when MaxDigit != 10 then we have to split into single digits
    while (x > 0) {
      sum += x % 10;
      x /= 10;
    }

  std::cout << sum << std::endl;
  return 0;
}