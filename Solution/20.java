import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        for (int a0 = 0; a0 < T; a0++) {
            BigInteger N = scanner.nextBigInteger();
            if (N.compareTo(BigInteger.valueOf(0)) == 0) {
                System.out.println("1");
                continue;
            }
            BigInteger sum = new BigInteger("0");
            BigInteger fact = N;
            while (N.compareTo(BigInteger.valueOf(1)) == 1) {
                fact = fact.multiply(N.subtract(BigInteger.valueOf(1)));
                N = N.subtract(BigInteger.valueOf(1));
            }
            while (fact.compareTo(BigInteger.valueOf(0)) == 1) {
                BigInteger temp = fact.mod(BigInteger.valueOf(10));
                sum = sum.add(temp);
                fact = fact.divide(BigInteger.valueOf(10));
            }
            System.out.println(sum);
        }
    }
}