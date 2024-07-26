import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in .nextInt();

        int result = 0;
        int maxcount = 0;

        int[] arr = new int[(int)(5 * Math.pow(10, 6) + 1)];
        for (int i = 2; i <= 3732423; i++) {
            int count = steps(i, 0);
            if (count > maxcount) {
                result = i;
                maxcount = count;
            } else if (count == maxcount) {
                result = i;
            }
            arr[i] = result;
        }

        for (int a0 = 0; a0 < t; a0++) {
            int no = in .nextInt();

            if (no > 3732423) {
                System.out.println(3732423);
            } else {
                System.out.println(arr[no]);
            }
        }
    }


    public static int steps(long num, int count) {

        while (num != 1) {
            if (num % 2 == 0) {
                count++;
                num = num / 2;
            } else {
                count++;
                num = num * 3 + 1;
            }
        }
        return count;

    }
}