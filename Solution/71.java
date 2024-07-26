import java.util.Scanner;

public class Solution {
    private static long R1_HIGH = 0;
    private static long R1_LOW = 0;
    private static long R2_HIGH = 0;
    private static long R2_LOW = 0;
    private static void multiply(long a, long b, int i) {
        long shift = 4 * Long.SIZE;
        long mask = (long) ~0 >> shift;

        long a_high = a >> shift;
        long a_low = a & mask;
        long b_high = b >> shift;
        long b_low = b & mask;

        long c_0 = a_low * b_low;
        long c_1a = a_high * b_low;
        long c_1b = a_low * b_high;
        long c_2 = a_high * b_high;

        long carry = ((c_0 >> shift) + (c_1a & mask) + (c_1b & mask)) >> shift;
        if (i == 1) {
            R1_HIGH = c_2 + (c_1a >> shift) + (c_1b >> shift) + carry;
            R1_LOW = c_0 + (c_1a << shift) + (c_1b << shift);
        } else if (i == 2) {
            R2_HIGH = c_2 + (c_1a >> shift) + (c_1b >> shift) + carry;
            R2_LOW = c_0 + (c_1a << shift) + (c_1b << shift);
        }
    }

    private static boolean isLess(long a, long b, long c, long d) {
        multiply(a, d, 1);
        multiply(c, b, 2);
        if (R1_HIGH < R2_HIGH) {
            return true;
        }
        if (R1_HIGH > R2_HIGH) {
            return false;
        }
        return (R1_LOW < R2_LOW);
    }

    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            int T = sc.nextInt();
            while (T > 0) {
                long a = sc.nextLong();
                long b = sc.nextLong();
                long N = sc.nextLong();
                long leftN = 0;
                long leftD = 1;
                long rightN = 1;
                long rightD = 1;
                while ((leftD + rightD) <= N) {
                    long mediantN = leftN + rightN;
                    long mediantD = leftD + rightD;
                    if (isLess(mediantN, mediantD, a, b)) {
                        leftN = mediantN;
                        leftD = mediantD;
                    } else {
                        rightN = mediantN;
                        rightD = mediantD;
                        if (rightN == a && rightD == b) {
                            break;
                        }
                    }
                }
                if (N >= (leftD + rightD)) {
                    long difference = N - (leftD + rightD);
                    long repeat = 1 + difference / rightD;
                    leftN += repeat * rightN;
                    leftD += repeat * rightD;
                }
                System.out.println(leftN + " " + leftD);
                T--;
            }
        }
    }
}