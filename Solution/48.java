import java.math.BigInteger;
import java.util.Scanner;

public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long t = in .nextLong();
        System.out.println(count(t));
    }


    public static String count(long num) {
        BigInteger modulus = BigInteger.TEN.pow(10);
        BigInteger sum = BigInteger.ZERO;
        for (int i = 1; i <= num; i++)
            sum = sum.add(BigInteger.valueOf(i).modPow(BigInteger.valueOf(i), modulus));
        return sum.mod(modulus).toString();
    }
}