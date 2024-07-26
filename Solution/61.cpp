#include <set>
#include <vector>
#include <iostream>

// all sums of valid sequences
std::set < unsigned int > results;

// 4 digits => all numbers must be below 10^4 = 10000
const unsigned int Limit = 10000;
// all number sets per number as a bitmask
std::vector < unsigned int > all(Limit, 0);

// bit mask of all categories (e.g. 1<<3 for triangle numbers, 1<<4 for square numbers, ...)
unsigned int finalMask = 0;

// add a category to a number
void add(unsigned int x, unsigned int category) {
  // reject if not exactly 4 digits
  if (x < 1000 || x >= 10000)
    return;

  // set one bit
  auto bit = 1 << category;
  // adjust its bitmask
  all[x] |= bit & finalMask;
}

void deeper(std::vector < unsigned int > & sequence, unsigned int mask = 0) {
  // all four digit-numbers
  unsigned int from = 1000;
  unsigned int to = 10000;

  if (!sequence.empty()) {
    // we only have to look at those numbers where the highest two digits match
    // the previous numbers lowest two digits
    auto lowerTwoDigits = sequence.back() % 100;
    from = lowerTwoDigits * 100;
    to = from + 100;
  }

  // try all relevant numbers
  for (auto next = from; next < to; next++) {
    auto categories = all[next];
    // not a member of any relevant set ?
    if (categories == 0)
      continue;

    // must not use the same number twice
    bool isUnique = true;
    for (auto x: sequence)
      if (x == next) {
        isUnique = false;
        break;
      }
    if (!isUnique)
      continue;

    // extract all categories it belongs to
    for (auto j = 3; j <= 8; j++) {
      auto thisCategory = 1 << j;
      // not a member of that category ?
      if ((categories & thisCategory) == 0)
        continue;

      // must be a new category we haven't seen yet in the current sequence
      if ((mask & thisCategory) != 0)
        continue;

      // we have all categories ?
      auto nextMask = mask | thisCategory;
      if (nextMask == finalMask) {
        // must compare against first number, too
        auto first = sequence.front();

        auto lowerTwoDigits = next % 100;
        auto upperTwoDigits = first / 100;

        if (lowerTwoDigits == upperTwoDigits) {
          // we found a result, store its sum
          auto sum = next;
          for (auto x: sequence)
            sum += x;
          results.insert(sum);
        }
      } else {
        // go deeper
        sequence.push_back(next);
        deeper(sequence, nextMask);
        sequence.pop_back();
      }
    }
  }
}

int main() {
  // only some sets are relevant to current problem
  unsigned int numSets;
  std::cin >> numSets;
  for (unsigned int i = 0; i < numSets; i++) {
    unsigned int x;
    std::cin >> x;
    finalMask |= 1 << x;
  }

  // build sets
  unsigned int n = 1;
  while (true) {
    auto triangle = n * (n + 1) / 2;
    // triangle numbers grow the slowest, once we have all of those then we are done
    if (triangle >= 10000)
      break;

    // add a triangle number
    add(triangle, 3);

    // add a square number
    auto square = n * n;
    add(square, 4);

    // add a pentagonal number
    auto pentagon = n * (3 * n - 1) / 2;
    add(pentagon, 5);

    // add a hexagonal number
    auto hexagon = n * (2 * n - 1);
    add(hexagon, 6);

    // add a heptagonal number
    auto heptagon = n * (5 * n - 3) / 2;
    add(heptagon, 7);

    // add an octagonal number
    auto octagon = n * (3 * n - 2);
    add(octagon, 8);

    n++;
  }

  // start search with an empty sequence
  std::vector < unsigned int > sequence;
  deeper(sequence);

  // print all results in ascending order
  for (auto x: results)
    std::cout << x << std::endl;

  return 0;
}