import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

public class Solution {

    public static boolean nextPermutation(char[] array) {
        for (int i = array.length - 1; i > 0; i--) {
            if (array[i - 1] < array[i]) {
                int dest = array[i - 1];
                int s = i;
                int e = array.length - 1;
                int swapIndex = 0;
                while (true) {
                    if (s == e) {
                        swapIndex = s;
                        break;
                    }
                    int m = (s + e + 1) / 2;
                    if (array[m] <= dest) {
                        e = m - 1;
                    } else {
                        s = m;
                    }
                }
                char temp = array[swapIndex];
                array[swapIndex] = array[i - 1];
                array[i - 1] = temp;
                Arrays.sort(array, i, array.length);
                return true;
            }
        }
        return false;
    }

    private static int ctoi(char[] data) {
        int result = 0;
        for (char d: data) {
            result *= 10;
            result += d - '0';
        }
        return result;
    }

    private static int upper_bound(ArrayList < Integer > list,
        int value) {
        int low = 0;
        int high = list.size();
        int mid;
        while (low < high) {
            mid = ((high - low) >>> 1) + low;
            if (list.get(mid) < value) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }

    public static void main(String[] args) {
        Set < Integer > sPrimes = new TreeSet < > ();
        sPrimes.add(2);
        for (int i = 3;
            (i * i) <= 987654321; i += 2) {
            boolean isPrime = true;
            for (int p: sPrimes) {
                if ((p * p) > i) {
                    break;
                }
                if ((i % p) == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                sPrimes.add(i);
            }
        }
        Set < Integer > pPrimes = new TreeSet < > ();
        for (int digits = 2; digits <= 9; digits++) {
            char[] sNumberArray = new char[digits];
            for (int s = 1; s <= digits; s++) {
                sNumberArray[s - 1] += s + '0';
            }
            do {
                int number = ctoi(sNumberArray);
                boolean isPrime = true;
                for (int p: sPrimes) {
                    if ((p * p) > number) {
                        break;
                    }
                    if ((number % p) == 0) {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime) {
                    pPrimes.add(number);
                }
            } while (nextPermutation(sNumberArray));
        }
        ArrayList < Integer > pPrimesList = new ArrayList < > (pPrimes);
        try (Scanner sc = new Scanner(System.in)) {
            int T = sc.nextInt();
            while (T-- > 0) {
                int N = sc.nextInt();
                int i = upper_bound(pPrimesList, N);
                if (i == 0 && pPrimesList.get(i) != N) {
                    System.out.println("-1");
                } else {
                    if (i == pPrimesList.size() ||
                        pPrimesList.get(i) != N) {
                        i--;
                    }
                    System.out.println(pPrimesList.get(i));
                }
            }
        }
    }
}