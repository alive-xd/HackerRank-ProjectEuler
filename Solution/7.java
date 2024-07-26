import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int[] arr = new int[10000000];
        for (int i = 2; i < 10000000; i++) {
            arr[i] = i;
        }
        for (int i = 2; i < 10000000; i++)
            for (int j = i + i; j < 10000000; j += i)
                arr[j] = 0;

        int t = in .nextInt();
        for (int a0 = 0; a0 < t; a0++) {
            int n = in .nextInt();
            int count = 0;
            for (int j = 2; j < 10000000; j++) {
                if (arr[j] != 0) {
                    count++;
                    if (count == n) {
                        System.out.println(j);
                        break;
                    }
                }
            }
        }
    }
}