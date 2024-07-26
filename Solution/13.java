import java.util.*;
import java.math.*;

public class Solution {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        BigInteger sum = new BigInteger("0");
        for (int i = 0; i < n; i++) {
            String s = sc.next();
            BigInteger bi = new BigInteger(s);
            sum = sum.add(bi);
        }
        System.out.println(String.valueOf(sum).substring(0, 10));
    }
}