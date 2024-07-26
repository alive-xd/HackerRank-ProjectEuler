#include <cstdio>
#include<cmath>
#include <iostream>

using namespace std;
int main() {
  int N;
  cin >> N;
  long int n[N], count[N], max = 0;
  for (int i = 0; i < N; i++) {
    cin >> n[i];
    count[i] = 0;
    if (max < n[i]) {
      max = n[i];
    }
  }

  for (long int i = 0; i <= max / 7; i++) {
    long int b2c = (i + 1) * (i + 1) * (8 * i + 5);
    long int a = 3 * i + 2;

    for (long int j = sqrt(b2c); j >= 1; j--) {
      if (b2c % (j * j) == 0 && b2c / (j * j) <= max) {
        long int b = j;
        long int c = b2c / (j * j);
        for (long int k = 0; k < N; k++)
          if (8 * a * a * a + 15 * a * a + 6 * a - 27 * b * b * c == 1 && (a + b + c <= n[k])) {
            count[k]++;
          }
      }
    }
  }
  for (int i = 0; i < N; i++) {
    cout << count[i] << endl;
  }
  return 0;
}