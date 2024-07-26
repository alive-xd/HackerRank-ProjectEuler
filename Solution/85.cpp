#include <iostream>
#include <cmath>

int main()
{
  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--)
  {
    unsigned int target = 2000000;
    std::cin >> target;

    // assume x <= y, therefore x <= sqrt(limit)
    unsigned int root = sqrt(target);
    unsigned int bestRectangles = 0;
    unsigned int bestArea       = 0;
    for (unsigned int x = 1; x <= root + 1; x++) // allow slight overshooting
    {
      // start with a sqaure
      unsigned int y = x;
      // number of rectangles
      unsigned int rectangles = 0;

      // slowly increase y until too many rectangle in the grid
      do
      {
        unsigned int area = x * y;

        // the formula derived above
        rectangles = x * (x + 1) * y * (y + 1) / 4;

        // closer to desired number of rectangles than before ?
        if (abs(bestRectangles - target) > abs(rectangles - target))
        {
          bestRectangles = rectangles;
          bestArea       = area;
        }

        // prefer larger areas, too (additional requirement of Hackerrank)
        if (abs(bestRectangles - target) == abs(rectangles - target) && bestArea < area)
          bestArea = area;

        y++;
      } while (rectangles < target);

      // just a speed-up ... abortion when the inner loop exited with a square area x*y
      // => it means that no further solutions possible, area already too large
      if (y == x + 1) // plus one because y was incremented before leaving the inner loop
        break;
    }
    std::cout << bestArea << std::endl;
  }
  return 0;
}
