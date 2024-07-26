import java.util.ArrayList;
import java.util.Scanner;

public class Solution {
    
    private static final ArrayList<Long> SO = new ArrayList<>();
    
    private static long sequence(long limit) {
        long[] plusOne = {1, 5};
        long[] minusOne = {1, 17};
        SO.clear();
        SO.add(3 * plusOne[1] + 1);
        SO.add(3 * minusOne[1] - 1);
        while(SO.get(SO.size() - 1) <= limit + 3) {
            long nextPlusOne = 14 * plusOne[1] - plusOne[0] - 4;
            long nextMinusOne = 14 * minusOne[1] - minusOne[0] + 4;
            plusOne[0] = plusOne[1];
            plusOne[1] = nextPlusOne;
            minusOne[0] = minusOne[1];
            minusOne[1] = nextMinusOne;
            SO.add(3 * nextPlusOne + 1);
            SO.add(3 * nextMinusOne - 1);
        }
        return SO.get(SO.size() - 1);
    }
    
    public static void main(String[] args) {
        SO.add(16L);
        long perimeter = 18;
        try(Scanner sc = new Scanner(System.in)) {
            int T = sc.nextInt();
            while(T-- > 0) {
                long N = sc.nextLong();
                while(perimeter <= N + 3) {
                    perimeter = sequence(N);
                }
                long sum = 0;
                sum = SO.stream().filter((x) -> (x <= N))
                                 .map((x) -> x)
                                 .reduce(sum, (accumulator, _item)
                                     -> accumulator + _item);
                System.out.println(sum);
            }
        }
    }
}
