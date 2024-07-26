import java.util.*;

public class Solution {

    public static long[] primes = {
        2,
        3,
        5,
        7,
        11,
        13,
        17,
        19,
        23,
        29,
        31,
        37
    };

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in .nextInt();
        for (int a0 = 0; a0 < t; a0++) {
            int n = in .nextInt();
            long output = 1;
            for (int i = 0; i < primes.length; i++) {
                long testDivisor = 1;
                while (testDivisor * primes[i] <= n) {
                    testDivisor *= primes[i];
                    output *= primes[i];
                }
            }
            System.out.println(output);
        }
    }
}