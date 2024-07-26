import java.util.Scanner;

public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in .nextInt();
        for (int a0 = 0; a0 < t; a0++) {
            long n = in .nextLong();
            long res = primeFactors(n);
            System.out.println(res);
        }
    }

    public static long primeFactors(long n) {
        while (n % 2 == 0) {
            n /= 2;
        }
        int res = 0;
        for (int i = 3; i <= Math.sqrt(n); i += 2) {
            while (n % i == 0) {
                n /= i;
                res = i;
            }
        }
        if (n > 2) {
            return n;
        } else {
            return res;
        }

    }
}