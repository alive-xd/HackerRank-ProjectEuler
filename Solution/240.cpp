#include <iostream>
#include <vector>

// configure environment
unsigned int numDice = 20; // 5;
unsigned int maxPoints = 12; // 6;
unsigned int numTop = 10; // 3;
unsigned int sumTop = 70; //15;

// 0! ... 20!
unsigned long long factorial[21];

// return number of permutations of dices
unsigned long long count(const std::vector < unsigned int > & dices) {
  static std::vector < unsigned int > howOften(maxPoints + 1, 0); // re-use the same vector
  // re-initialize
  for (auto & x: howOften)
    x = 0;

  // count how often we see each side (1,2,3,...,6 or ...,12)
  for (auto x: dices)
    howOften[x]++;

  // n! / (ones! * twos! * threes! * ...)
  unsigned long long result = factorial[numDice];
  for (auto x: howOften)
    if (x > 1) // factorial[0] = factorial[1] = 1 ==> no need to divide
      result /= factorial[x];

  return result;
}

// generate all dices in descending order
// then compute how many permutations  exist for each combination
unsigned long long search(std::vector < unsigned int > & dices) {
  // enough dices ?
  if (dices.size() == numDice)
    return count(dices);

  // check top dices: "hit the spot" ?
  if (dices.size() == numTop) {
    unsigned int sum = 0;
    for (auto x: dices)
      sum += x;

    // no, top dices' sum is either too high or too low => abort
    if (sum != sumTop)
      return 0;
  }

  // add one more dice - always in descending order, never higher than the previous dice
  unsigned int maxDice = maxPoints;
  if (!dices.empty())
    maxDice = dices.back();

  // all possible dices ...
  unsigned long long result = 0;
  for (unsigned int dice = 1; dice <= maxDice; dice++) {
    dices.push_back(dice);
    result += search(dices);
    dices.pop_back(); // re-use the same vector over and over again (for performance reasons)
  }

  return result;
}

int main() {
  std::cin >> numDice >> maxPoints >> numTop >> sumTop;
  // catch invalid input
  if (numTop > numDice)
    return 1;

  // precompute factorials 0! .. 20!
  factorial[0] = 1;
  unsigned long long current = 1;
  for (unsigned int i = 1; i <= numDice; i++) {
    current *= i;
    factorial[i] = current;
  }

  // and go !
  std::vector < unsigned int > dices;
  std::cout << search(dices) << std::endl;
  return 0;
}