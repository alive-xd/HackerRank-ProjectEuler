import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long t = in .nextLong();
        for (int a0 = 0; a0 < t; a0++) {
            int n = in .nextInt();
            System.out.println(SumSquaredifference(n));
        }
    }

    public static long SumSquaredifference(long n) {
        if (n == 1)
            return 0;

        return SumSquaredifference(n - 1) + n * n * (n - 1);
    }
}