import java.util.*;

public class Solution {

    public static void main(String[] args) {
        int n = new Scanner(System.in).nextInt();
        long sum = 0;
        for (long i = (long) Math.pow(10, 0); i <= (long) 2 * Math.pow(10, n); i++) {
            String ok = "" + i;
            int add = 0;
            for (int j = 0; j < ok.length(); j++) {
                add += (long) Math.pow(Integer.valueOf("" + ok.charAt(j)), n);
            }
            if (add == i && i != 1) {
                sum += i;
            }
        }
        System.out.println(sum);
    }
}