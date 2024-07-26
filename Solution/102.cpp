#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int tri, j = 0, count = 0;
  double x1, y1, x2, y2, x3, y3;
  cin >> tri; //no of triangles
  double area, area1, area2, area3;
  for (int i = 0; i < tri; i++) {
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    area = abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2);
    area1 = abs((0 * (y2 - y3) + x2 * (y3 - 0) + x3 * (0 - y2)) / 2.0);
    area2 = abs((x1 * (0 - y3) + 0 * (y3 - y1) + x3 * (y1 - 0)) / 2.0);
    area3 = abs((x1 * (y2 - 0) + x2 * (0 - y1) + 0 * (y1 - y2)) / 2.0);
    if (area == (area1 + area2 + area3)) {
      count++;
    }

  }
  cout << count;
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  return 0;
}