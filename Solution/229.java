import java.io.*;
import java.util.*;

public class Solution {

    private boolean isEuler(final int Number) {
        boolean Fin = true, unfin[] = {
            false,
            false,
            false,
            false
        };
        for (int i = 1; i <= Math.sqrt(Number); i++) {
            for (int j = 1; j <= Math.sqrt(Number); j++) {
                if (((i * i) + (j * j)) == Number) {
                    unfin[0] = true;
                    break;
                }
            }
        }
        for (int i = 1; i <= Number / 2; i++) {
            for (int j = 1; j <= Number / 2; j++) {
                if (((i * i) + (2 * j * j)) == Number) {
                    unfin[1] = true;
                    break;
                }
            }
        }
        for (int i = 1; i <= Number / 2; i++) {
            for (int j = 1; j <= Number / 2; j++) {
                if (((i * i) + (3 * j * j)) == Number) {
                    unfin[2] = true;
                    break;
                }
            }
        }
        for (int i = 1; i <= Number / 2; i++) {
            for (int j = 1; j <= Number / 2; j++) {
                if (((i * i) + (7 * j * j)) == Number) {
                    unfin[3] = true;
                    break;
                }
            }
        }
        //System.out.println(unfin[0]+unfin[1]+unfin[2]);
        return unfin[0] && unfin[1] && unfin[2] && unfin[3];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int q = sc.nextInt();
        int c = 0;
        Solution obj = new Solution();
        for (int i = 1; i <= q; i++) {
            int n = sc.nextInt();
            for (int j = 1; j <= n; j++)
                if (obj.isEuler(j)) {
                    c++;
                }
            System.out.println(c);
            c = 0;
        }
    }
}