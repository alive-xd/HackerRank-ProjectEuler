import java.io.*;
import java.util.*;
import java.math.*;
public class Solution {

    public static void main(String args[]) {
        BigInteger table[] = new BigInteger[100001];

        int coin[] = new int[] {
            1,
            2,
            5,
            10,
            20,
            50,
            100,
            200
        };
        for (int i = 0; i < table.length; i++) {
            table[i] = BigInteger.ZERO;
        }
        table[0] = BigInteger.ONE;
        for (int i = 0; i < 8; i++) {
            for (int j = coin[i]; j < table.length; j++) {
                table[j] = table[j].add(table[j - coin[i]]);
            }
        }
        Scanner sc = new Scanner(System.in);
        int num = Integer.parseInt(sc.nextLine());
        for (int i = 0; i < num; i++) {
            int tem = Integer.parseInt(sc.nextLine());
            System.out.println(table[tem].mod(BigInteger.valueOf(1000000007)));
        }
    }
}