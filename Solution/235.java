import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.DecimalFormat;

class Solution {
    static double solver(int n, long x, int a, int d) {
        double arr[] = bounds(n, x, a, d);
        double lb = arr[0];
        double ub = arr[1];
        double tol = 0.0000000000001;
        final int maxiter = 100;
        int i = 0;
        double intermediate = (lb + ub) / 2;
        while (i <= maxiter) {
            intermediate = (lb + ub) / 2;
            if (function(n, x, a, d, intermediate) == 0 || (ub - lb) < tol)
                return intermediate;
            else if (sign(function(n, x, a, d, lb)) == sign(function(n, x, a, d, intermediate))) {
                lb = intermediate;
            } else
                ub = intermediate;
            i++;
        }

        if (i > maxiter)
            return -101;
        else
            return -404;
    }

    static double[] bounds(int n, long x, int a, int d) {
        double lb = 0.1D, ub = 0.1D;
        int flag = 0;
        int c = 0;
        for (double i = -0.1; i > -10; i = i - 0.1) {
            for (double j = 0; j < 10; j = j + 0.1) {
                if (function(n, x, a, d, i) * function(n, x, a, d, j) < 0) {
                    lb = i;
                    ub = j;
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) {
                break;
            }

        }
        double[] ar = {
            lb,
            ub
        };
        return ar;
    }

    static double
    function(int n, long x, int a, int d, double r) {
        double f = 0.0D;
        double c1 = a - n * d;
        double c2 = -a;
        f = d * (Math.pow(r, n) - 1) + (r - 1) * (c1 * Math.pow(r, n) + c2) + x * (r - 1) * (r - 1);
        return f;

    }

    static int sign(double x) {
        if (x < 0)
            return 1;
        else if (x > 0)
            return 0;
        else
            return -1;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int q = Integer.parseInt(br.readLine());
        int i = 0;
        String S = "";
        int a = 0, n = 0, d = 0;
        long x = 0L;
        DecimalFormat ob = new DecimalFormat("#.################");
        while (i < q) {
            S = br.readLine();
            String str[] = S.split(" ");
            a = Integer.parseInt(str[0]);
            d = Integer.parseInt(str[1]);
            n = Integer.parseInt(str[2]);
            x = Long.parseLong(str[3]);
            double r = 0.0D;
            double v = (double)(a * n - d * n * n / 2.0 - d * n / 2.0);
            if (v == -x)
                r = 1.0;
            else
                r = solver(n, x, a, d);
            System.out.println(ob.format(r));
            i++;
        }
    }
}