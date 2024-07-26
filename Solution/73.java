import java.util.Scanner;

public class Solution {
    private static int A;

    private static long rank(int n, long d) {
        long[] data = new long[A + 1];
        for (int i = 0; i < data.length; i++) {
            data[i] = i * n / d;
        }
        for (int i = 1; i < data.length; i++) {
            for (int j = 2 * i; j < data.length; j += i) {
                data[j] -= data[i];
            }
        }
        long sum = 0;
        for (long x: data) {
            sum += x;
        }
        return sum;
    }

    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            long D = sc.nextInt();
            A = sc.nextInt();
            long fromD = D + 1;
            System.out.println(rank(1, D) - rank(1, fromD) - 1);
        }
    }
}