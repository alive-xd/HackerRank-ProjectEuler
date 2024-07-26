import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        long n = scan.nextLong();
        long k = scan.nextLong();
        int a = (int) Math.pow(2, k);
        long count = n / a;
        for (long i = 3; Math.pow(i, k) <= n; i += 2) {
            if (prime(i)) {
                a = (int) Math.pow(i, k);
                count += n / a;
            }
        }
        System.out.println(n - count);
    }

    public static boolean prime(long n) {
        if (n % 2 == 0)
            return false;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0)
                return false;
        }
        return true;
    }
}