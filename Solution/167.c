#include<stdio.h>

int main() {
  int i, n, num;
  long k;
  scanf("%d %ld", & n, & k);
  int arr[k];
  arr[0] = 2;
  arr[1] = (2 * n) + 1;
  num = arr[0] + arr[1];
  for (i = 2; i < k; num++) {
    if (sumcheck(num, arr, i)) {
      arr[i] = num;
      i++;
    }
  }
  printf("%d", arr[k - 1]);
  return 0;
}
int sumcheck(int num, int arr[], int size) {
  int i, j, k = 0;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      if (arr[j] + arr[i] == num) {
        k++;
      }
    }
  }
  if (k == 2) {
    return 1;
  } else {
    return 0;
  }
}