import java.util.*;

public class Solution {

    /*
      the first element is the amicable number, the second element is the sum of
      all the amicable numbers not greater than the first element
      [[220, 220], [284, 504], [1184, 1688], [1210, 2898], [2620, 5518], [2924,
      8442], [5020, 13462], [5564, 19026], [6232, 25258], [6368, 31626], [10744,
      42370], [10856, 53226], [12285, 65511], [14595, 80106], [17296, 97402],
      [18416, 115818], [63020, 178838], [66928, 245766], [66992, 312758], [67095,
      379853], [69615, 449468], [71145, 520613], [76084, 596697], [79750, 676447],
      [87633, 764080], [88730, 852810]]
      */
    static long[][] result = null;
    //1<=N<=100000
    static int limit = 100000;
    /*
     * initialization
     */
    static {
        //stores the amicable numbers
        Set < Integer > set = bar(limit);
        int k = 0;
        result = new long[set.size()][2];

        for (Integer i: set) {
            result[k][0] = i;
            if (k > 0) {
                result[k][1] = result[k - 1][1] + i;
            } else {
                result[k][1] = i;
            }
            k++;
        }
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in .nextInt();
        while (t-- > 0) {
            int N = in .nextInt();
            getResult(N);
        } in .close();
    }

    private static int foo(int N) {
        int sum = 0;
        for (int i = 2; i * i < N; i++) {
            if (N % i == 0)
                sum += (i + N / i);
        }
        if (sum == 0)
            return sum;
        // add 1
        sum++;
        if (sum == N)
            return 0;
        return sum;
    }

    private static TreeSet < Integer > bar(int N) {
        TreeSet < Integer > set = new TreeSet < > ();
        for (int i = 2; i <= N; i++) {
            if (set.contains(i))
                continue;
            int k = foo(i); // converted
            int M = foo(k);
            if (M == i) {
                set.add(i);
                set.add(k);
            }
        }
        return set;
    }

    private static void getResult(int N) {
        if (N <= result[0][0]) {
            System.out.println(0);
        } else if (N > result[result.length - 1][0]) {
            System.out.println(result[result.length - 1][1]);
        } else {
            for (int i = 1; i < result.length; i++) {
                if (N < result[i][0]) {
                    System.out.println(result[i - 1][1]);
                    break;
                }
            }
        }
    }
}