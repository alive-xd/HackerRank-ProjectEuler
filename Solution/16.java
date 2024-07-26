import java.util.*;
import java.math.BigInteger;
public class Solution {

    public static void main(String gg[]) {
        Scanner scanner = new Scanner(System.in);
        int numberOfTestCases = scanner.nextInt();
        int number = 0;
        long sum = 0;
        while (numberOfTestCases != 0) {
            sum = 0;
            number = scanner.nextInt();
            BigInteger bb = new BigInteger("2");
            bb = bb.pow(number);
            String s = bb.toString();
            char c[] = s.toCharArray();
            for (char cc: c) {
                sum += (((int) cc) - 48);
            }
            System.out.println(sum);
            --numberOfTestCases;
        }
    }

}