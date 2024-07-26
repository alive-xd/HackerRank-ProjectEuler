import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class Solution {
    
    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)) {
            int N = sc.nextInt();
            Map<Double, int[]> data = new TreeMap<>();
            for(int i = 1; i <= N; i++) {
                int B = sc.nextInt();
                int E = sc.nextInt();
                int[] input_datas = {B, E};
                data.put(E * Math.log(B), input_datas);
            }
            int K = sc.nextInt() - 1;
            int index = 0;
            for(int[] i : data.values()) {
                if(index == K) {
                    System.out.println(i[0] + " " + i[1]);
                    break;
                }
                index++;
            }
        }
    }
}
