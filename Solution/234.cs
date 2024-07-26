using System;
using System.Collections.Generic;
using System.IO;

class Solution {
  static void Main(String[] args) {

    string[] lr = Console.ReadLine().Split(' ');
    long l = Convert.ToInt64(lr[0]);
    long r = Convert.ToInt64(lr[1]);
    long sum = 0;

    for (long number = l; number <= r; number++) {
      double lps = Math.Floor(Math.Sqrt(number));
      double ups = Math.Ceiling(Math.Sqrt(number));

      for (int i = 2; i < number / 2; i++) {
        if (i >= lps && lps > 2) {
          break;
        }
        if (lps % i == 0 && lps > 2) {
          lps--;
          i = 1;
        }
      }

      for (int i = 2; i < number / 2; i++) {
        if (i >= ups) {
          break;
        }
        if (ups % i == 0) {
          ups++;
          i = 1;
        }
      }

      if (number == (lps * lps)) {} else if (number % lps == 0 && number % ups == 0) {} else if (number % lps != 0 && number % ups != 0) {} else {
        sum = sum + number;
      }

    }

    Console.WriteLine(sum);
    Console.ReadLine();
  }
}