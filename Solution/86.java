import java.util.ArrayList;
import java.util.Scanner;

public class Solution {
    
    private static int getSquareRoot(long a) {
        long f = 0;
        int ret = 0;
        for(long i = 0; i < 16; i++) {
            ret <<= 1;
            long kari_f = (f + 1) << ((15 - i) * 2);
            if(a >= kari_f) {
                f = f + 2;
                a -= kari_f;
                ret++;
            }
            f <<= 1;
        }
        return ret;
    }
    
    private static int combinations(int a, int b_c) {
        if(2 * a < b_c) {
            return 0;
        }
        if(a >= b_c) {
            return b_c / 2;
        }
        return a - (b_c - 1) / 2;
    }
    
    private static int gcd(int a, int b) {
        while(a != 0) {
            int temp = a;
            a = b % a;
            b = temp;
        }
        return b;
    }
    
    private static long[] countAll(int limit) {
        long[] solutions = new long[limit + 1];
        for(int m = 1; m <= getSquareRoot(2 * limit); m++) {
            for(int n = 1; n < m; n++) {
                if((m % 2) != (n % 2) && gcd(m, n) == 1) {
                    int x = m * m - n * n;
                    int y = 2 * m * n;
                    for(int k = 1; k * x <= limit; k++) {
                        solutions[k * x] += combinations(k * x, k * y);
                    }
                    for(int k = 1; k * y <= limit; k++) {
                        solutions[k * y] += combinations(k * y, k * x);
                    }
                }
            }
        }
        return solutions;
    }
    
    public static void main(String[] args) {
        long[] solutions = countAll((int) Math.pow(10, 6));
        ArrayList<Long> total = new ArrayList<>();
        long sum = 0;
        for(long i : solutions) {
            sum += i;
            total.add(sum);
        }
        try(Scanner sc = new Scanner(System.in)) {
            int T = sc.nextInt();
            while(T-- > 0) {
                int N = sc.nextInt();
                System.out.println(total.get(N));
            }
        }
    }
}
