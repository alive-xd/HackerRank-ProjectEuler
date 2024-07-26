#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
  int a, b, c, d, g;
  scanf("%d%d%d%d", & a, & b, & c, & d);
  int check(int, int, int, int);
  g = check(a, b, c, d);
  printf("%d", g);
  return 0;
}

int check(int x, int y, int z, int w) {
  int k = 0, e, a, b, c, u;
  for (e = 1; k != w; e += 2) {
    a = x;
    b = y;
    c = z;
    u = a + b + c;
    while (u % e != 0) {
      a = b;
      b = c;
      c = u % e;
      u = a + b + c;
      if (a == x && b == y && c == z) {
        k++;
        break;
      }
    }
  }

  return e - 2;
}