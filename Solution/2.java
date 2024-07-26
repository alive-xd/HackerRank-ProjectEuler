import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in .nextInt();
        for (int a0 = 0; a0 < t; a0++) {
            long n = in .nextLong();
            long first = 1;
            long second = 2;
            long sum = second;
            for (long i = 3; second < n; i++) {
                long temp = second;
                second = second + first;
                first = temp;
                if (second % 2 == 0 && second < n)
                    sum += second;
            }
            System.out.println(sum);
        }
    }
}