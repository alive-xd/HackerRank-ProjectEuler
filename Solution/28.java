import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Solution {
private static long modulo = 1000_000_000 + 7;
    
    private static BigInteger modInt =  new BigInteger(modulo + "");

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        while (t-- > 0) {
            long N = in.nextLong();
            if (1L == N)
                System.out.println(N);
            else
                bar(N);
        }
        in.close();
    }
    
    private static void useBigInteger(long n) {
        n /= 2;
        BigInteger k1 = new BigInteger(n + "");
        BigInteger k2 = new BigInteger((n+1) + "");
        BigInteger k3 = new BigInteger((8) + "");
        BigInteger k4 = new BigInteger((2*n+1) + "");
        long m = k1.multiply(k2).multiply(k3).multiply(k4).divide(new BigInteger(3 + "")).mod(modInt).intValue();
		// System.out.println(m);
        long q = k1.multiply(k2).multiply(new BigInteger(2 + "")).mod(modInt).intValue();
		// System.out.println(q);
        long c = k1.multiply(new BigInteger(4 + "")).mod(modInt).longValue();
		// System.out.println("c=" + c);
        long d = 1;
        long big = (m + q + c + d) % modulo;
        System.out.println(big);
    }

    /**
     * d1 = (2n + 1) ^2 Hence d1 = 4n^2 + 4n + 1 
     * The numbers along the other
     * diagonals are simply derived from d1 by subtracting certain values. 
     * d2 = d1 - 2n Hence d2 = 4n^2 + 2n + 1 
     * d3 = d2 - 2n Hence d3 = 4n^2 + 1 
     * d4 = d3 - 2n Hence d4 = 4n^2 - 2n + 1 
     * Now, all that the problem asks us to do is to sum up
     * the numbers d1, d2, d3, d4 for n = 1, 2, 3, . . . . .. . .. 
     * sum = summation of (16n^2 + 4n + 4) for n = 1, 2, 3, . . . . . 
     * Now sum up remaining things like 
     * 16 * summation of n^2 = 8 * n * (n+1) * (2 * n + 1) / 3 
     * 4 * summation of n = 2 * (n) * (n+1) 
     * summation of 4 = 4 * n
     * 
     * @param n
     * @return
     */
    private static int bar(long n) {
        // System.out.println(n + "----------------");
        n /= 2;
        //first step: calculate the summation
		// long sum = (long) (1+8*n*(n+1)*(2*n+1)/3+2*(n)*(n+1)+4*n);
		// long partA = 8*n*(n+1)*(2*n+1)/3;
		// long partB = 2*(n)*(n+1);
		// long partC = 4*n;
		// long partD = 1;
        //second step: calculate the remainder
        long[] numbers = new long[]{n, n + 1, 2 * n + 1};
        replaceDividible(numbers);
        long a = inverseModulo(modulo, 8, numbers);
		// System.out.println("a=" + a);
        numbers = new long[]{n, n + 1};
        long b = inverseModulo(modulo, 2, numbers);
		// System.out.println("b=" + b);
        numbers = new long[]{n};
        long c = inverseModulo(modulo, 4, numbers);
		// System.out.println("c=" + c);
        long d = 1;
		// System.out.println("(int) ((a + b + c + d) % modulo)=" + (int) ((a + b + c + d) % modulo));
        long raw = (a + b + c + d) % modulo;
        System.out.println(raw);
        return 0;

    }
    
    /**
     * replace the value of the number that is divisible by 3
     * @param a
     */
    private static void replaceDividible(long[] a) {
        for (int i = 0; i < a.length; i++) {
            if (a[i] % 3 == 0L) {
                a[i] /= 3;
            }
        }
    }

    private static int inverseModulo(long modulo, long base, long[] numbers) {
        base = base % modulo;
        //reduce to be below integer type
        for (int i = 0; i < numbers.length; i++) {
            numbers[i] %= modulo;
        }
        for (long i : numbers) {
            base = (base * i) % modulo;
        }
        return (int) base;
    }
}
