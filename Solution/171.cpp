#include <iostream>
#include <vector>

// precompute factorials
std::vector < unsigned long long > factorials;
// highest digit sum is 20*9, precompute for each number whether it's a square
std::vector < unsigned char > isSquare; // actually a bit faster than std::vector<bool>

// only the last 9 digits
const unsigned long long Modulo = 1000000000;

// return the sum of all numbers that can be made with all the digits supplied by parameter "digits"
unsigned long long count(const std::vector < unsigned int > & digits) {
  // sum of all squared digits
  unsigned int sum = 0;
  // and number of digits (always 20)
  unsigned int count = 0;
  for (size_t current = 0; current < digits.size(); current++) {
    sum += digits[current] * current * current;
    count += digits[current];
  }

  // proceed only if sum is a perfect square
  if (!isSquare[sum])
    return 0;

  // https://www.quora.com/What-is-a-formula-to-calculate-the-sum-of-all-the-permutations-of-a-given-number-with-repitations
  unsigned long long result = factorials[count];
  for (auto x: digits)
    result /= factorials[x];

  unsigned long long numerator = 0;
  for (size_t current = 0; current < digits.size(); current++)
    numerator += current * digits[current];
  result *= numerator;
  result /= count;

  // (10^count-1)/9 is a bunch of ones (111...111) or "repunit"
  // the result is modulo 10^9 therefore I need at most a repunit with 9 digits
  unsigned long long ones = 1;
  for (unsigned int i = 2; i <= count && i <= 9; i++)
    ones = ones * 10 + 1;
  // if result is large and then multiplied by a large repunit then I get overflows
  // only the lowest 9 digits are relevant anyway, truncate result before multiplication
  result %= Modulo;
  // at most 9 times 9 digits, that's fine with 64 bit arithmetic
  result *= ones;

  // and only the lowest 9 digits are of interest anyway
  return result % Modulo;
}

// recursively add digit-by-digit and call count() after 20 digits
unsigned int search(std::vector < unsigned int > & digits, unsigned int atLeastDigit, unsigned int digitsLeft) {
  // all digits processed, find sum of all combinations
  if (digitsLeft == 0)
    return count(digits);

  // append one more digit, must not be lower than any previous
  unsigned long long result = 0;
  for (unsigned int current = atLeastDigit; current <= 9; current++) {
    // adjust number of digits
    digits[current]++;
    result += search(digits, current, digitsLeft - 1);
    // and revert
    digits[current]--;
  }

  return result % Modulo;
}

int main() {
  unsigned int result = 0;

  // number of digits
  unsigned int numDigits = 20;

  // assume only 10^k as input (which it isn't for most test cases)
  unsigned long long limit; // too small for > 10^20
  std::cin >> limit;

  // quick hack: Hackerrank includes the last number, e.g. 10^k
  result += limit % Modulo;
  // count digits of 10^k (=> determine k)
  numDigits = 0;
  while (limit > 1) {
    numDigits++;
    limit /= 10;
  }

  // precompute factorials
  // 0! = 1
  factorials.push_back(1);
  // and 1! ... 20!
  for (unsigned int i = 1; i <= numDigits; i++)
    factorials.push_back(i * factorials.back());

  // and squares: 20 digits, each is at most 9^2
  const unsigned int MaxSquare = 20 * 9 * 9;
  isSquare.resize(MaxSquare, false);
  for (unsigned int i = 1; i * i <= MaxSquare; i++)
    isSquare[i * i] = true;

  // "empty" number, none of the digits 0..9 is initially used
  std::vector < unsigned int > digits(10, 0);
  result += search(digits, 0, numDigits);
  std::cout << result << std::endl;
  return 0;
}