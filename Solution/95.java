import java.util.ArrayList;
import java.util.Scanner;

public class Solution {
    
    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)) {
            int N = sc.nextInt();
            ArrayList<Integer> primes = new ArrayList<>();
            primes.add(2);
            for(int i = 3; i <= N; i++) {
                boolean isPrime = true;
                for(int p : primes) {
                    if((p * p) > i) {
                        break;
                    }
                    if((i % p) == 0) {
                        isPrime = false;
                        break;
                    }
                }
                if(isPrime) {
                    primes.add(i);
                }
            }
            int[] divSum = new int[N + 1];
            for(int i = 2; i <= N; i++) {
                int sum = 1;
                int reduce = i;
                for(int p : primes) {
                    if((p * p) > reduce) {
                        break;
                    }
                    int factor = 1;
                    while((reduce % p) == 0) {
                        reduce /= p;
                        factor *= p;
                        factor++;
                    }
                    sum *= factor;
                }
                if(reduce > 1 && reduce < i) {
                    sum *= reduce + 1;
                }
                if(sum > 1) {
                    sum -= i;
                }
                divSum[i] = sum;
            }
            int longestChain = 0;
            int smallestMember = N;
            for(int i = 1; i <= N; i++) {
                ArrayList<Integer> chain = new ArrayList<>();
                chain.clear();
                chain.add(i);
                while(true) {
                    int add = divSum[chain.get(chain.size() - 1)];
                    chain.add(add);
                    if(add == i) {
                        break;
                    }
                    if(add < i) {
                        break;
                    }
                    if(add > N) {
                        break;
                    }
                    boolean isLoop = false;
                    for(int j = 1; j < chain.size() - 1; j++) {
                        if(add == chain.get(j)) {
                            isLoop = true;
                            break;
                        }
                    }
                    if(isLoop) {
                        break;
                    }
                }
                if(chain.get(chain.size() - 1) == i) {
                    if(chain.size() >= longestChain) {
                        if(longestChain < chain.size()) {
                            longestChain = chain.size();
                            smallestMember = chain.get(0);
                        }
                    }
                }
            }
            System.out.println(smallestMember);
        }
    }
}
