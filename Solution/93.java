import java.util.ArrayList;
import java.util.Scanner;

public class Solution {
    
    private static final double EPSILON = 0.00001;
    
    private static void eval(ArrayList<Double> numbers, boolean[] used) {
        if(numbers.size() == 1) {
            double result = numbers.get(0) + EPSILON;
            if((result % 1.0) <= 10 * EPSILON) {
                int index = (int) (result + EPSILON);
                if(index >= 0 && index < used.length) {
                    used[index] = true;
                }
            }
        } else {
            //step 2
            ArrayList<Double> next;
            for(int i = 0; i < numbers.size(); i++) {
                for(int j = i + 1; j < numbers.size(); j++) {
                    double a = numbers.get(i);
                    double b = numbers.get(j);
                    next = new ArrayList<>(numbers);
                    next.remove(j);
                    next.remove(i);
                    next.add(a + b);
                    eval(next, used);
                    int back = next.size() - 1;
                    next.set(back, a - b);
                    eval(next, used);
                    next.set(back, b - a);
                    eval(next, used);
                    next.set(back, a * b);
                    eval(next, used);
                    if(b != 0) {
                        next.set(back, a / b);
                        eval(next, used);
                    }
                    if(a != 0) {
                        next.set(back, b / a);
                        eval(next, used);
                    }
                }
            }
        }
    }
    
    private static int getSequenceLength(ArrayList<Double> numbers) {
        boolean[] used = new boolean[1000];
        eval(numbers, used);
        int result = 0;
        while(used[result + 1]) {
            result++;
        }
        return result;
    }
    
    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)) {
            int N = sc.nextInt();
            ArrayList<Double> numbers = new ArrayList<>();
            while(N-- > 0) {
                numbers.add(sc.nextDouble());
            }
            System.out.println(getSequenceLength(numbers));
        }
    }
}
