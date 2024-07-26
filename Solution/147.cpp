#include <iostream>
#include <map>

// Hackerrank only
const unsigned int Modulo = 1000000007;

// return number of different rectangles in a x*y grid (without diagonal rectangles)
unsigned int grid(unsigned int width, unsigned int height) {
  // triangular number, see https://en.wikipedia.org/wiki/Triangular_number
  // return T(width) * T(height)
  return (width * (width + 1) / 2) * (height * (height + 1) / 2);
}

// return number of different diagonal rectangles in a x*y grid
unsigned int diagonal(unsigned int width, unsigned int height) {
  // memoize
  static std::map < std::pair < unsigned int, unsigned int > , unsigned int > cache;
  auto id = std::make_pair(width, height);
  auto lookup = cache.find(id);
  if (lookup != cache.end())
    return lookup -> second;

  // a is the length of the longer side and b the shorter side
  auto a = width;
  auto b = height;
  if (a < b)
    std::swap(a, b);

  // no clever formulas, just stupid counting ...
  unsigned int count = 0;

  // for each lattice point (x,y) I can find two nearby square centers:
  // at (x + 0.5, y) and at (x, y + 0.5)
  // floating-point arithmetic was a bit slow therefore I switched to integer arithmetic:
  // all coordinates are multiplied by 2
  for (unsigned int i = 0; i < a; i++)
    for (unsigned int j = 0; j < b; j++)
      for (unsigned int parity = 0; parity <= 1; parity++) {
        // left-most corner (if rotated by 45 degrees it would be the lower-left corner)
        auto startX = 2 * i + 1 + parity;
        auto startY = 2 * j + 2 - parity;
        // now try to find all possible upper-right corners of that triangle

        // found all rectangles started at (startX, startY) ?
        bool stop = false;
        // limit height of each rectangle
        auto maxHeight = 999999999;

        // scan along the (rotated) x-axis
        for (auto currentWidth = 0; !stop; currentWidth++) {
          // generate coordinates in a non-rotated coordinate system (still multiplied by 2)
          auto currentX = startX + currentWidth;
          auto currentY = startY - currentWidth;
          // out of bounds ?
          if (currentY <= 0)
            break;

          // scan along the (rotated) y-axis
          // note: not higher than any rectangle before (with the same starting point)
          for (auto currentHeight = 0; currentHeight < maxHeight; currentHeight++) {
            // upper-right corner of the current rectangle
            auto endX = currentX + currentHeight;
            auto endY = currentY + currentHeight;
            if (endX >= 2 * a || endY >= 2 * b) {
              // no other rectangle may be higher
              if (maxHeight > currentHeight)
                maxHeight = currentHeight;

              // reached right-most part ? => done
              stop = (currentHeight == 0);
              break;
            }

            // found one more rectangle
            count++;
          }
        }
      }

  cache[id] = count;
  return count;
}

int main() {
  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--) {
    unsigned int maxWidth = 47;
    unsigned int maxHeight = 43;
    std::cin >> maxWidth >> maxHeight;

    // count all upright and all diagonal rectangles
    unsigned long long sumUpright = 0;
    unsigned long long sumDiagonal = 0;
    for (unsigned int width = 1; width <= maxWidth; width++)
      for (unsigned int height = 1; height <= maxHeight; height++) {
        sumUpright += grid(width, height);
        sumDiagonal += diagonal(width, height);
      }

    // display result

    std::cout << sumUpright % Modulo << " " << sumDiagonal % Modulo << std::endl;

  }

  return 0;
}