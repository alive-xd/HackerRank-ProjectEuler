import java.util.Arrays;
import java.util.HashSet;
import java.util.Scanner;

public class Solution {

    private static char[] insert(char[] array, int count, char target) {
        char[] in_new = new char[array.length + count];
        for (int k = 0; k < count; k++) {
            in_new[k] = target;
        }
        for (int k = count; k < in_new.length; k++) {
            in_new[k] = array[k - count];
        }
        return in_new;
    }

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

    private static char[] NumToCharArray(int x, int digits) {
        String result = String.valueOf(x);
        while (result.length() != digits) {
            result = "0" + result;
        }
        return result.toCharArray();
    }

    private static int merge(char[] strFill, char[] mask) {
        int index = 0;
        int result = 0;
        for (char m: mask) {
            result *= 10;
            if (m == '.') {
                result += strFill[index] - '0';
                index++;
            } else {
                result += Character.getNumericValue(m);
            }
        }

        return result;
    }

    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            int N = sc.nextInt();
            int K = sc.nextInt();
            int keep = N - K;
            int[] Tens = {
                1,
                10,
                100,
                1000,
                10000
            };
            int sumN = 0;
            int sumD = 0;
            HashSet < Integer > used = new HashSet < > ();
            for (int d = 1; d < Tens[keep]; d++) {
                for (int n = 1; n < d; n++) {
                    char[] charN = NumToCharArray(n, keep);
                    char[] charD = NumToCharArray(d, keep);
                    for (int i = Tens[K - 1]; i < Tens[K]; i++) {
                        char[] in = NumToCharArray(i, K);
                        boolean isAscending = true;
                        for (int j = 1; j < in .length; j++) {
                            if ( in [j - 1] > in [j]) {
                                isAscending = false;
                                break;
                            }
                        }
                        if (isAscending) { in = insert( in , keep, '.');
                            char[] charInsertN = in .clone();
                            do {
                                int newN = merge(charN,
                                    charInsertN);
                                if (newN >= Tens[N - 1]) {
                                    char[] charInsertD = in .clone();
                                    do {
                                        int newD = merge(charD,
                                            charInsertD);
                                        if (newN * d == newD * n) {
                                            int id = newN *
                                                10000 +
                                                newD;
                                            if (!used.contains(id)) {
                                                sumN += newN;
                                                sumD += newD;
                                                used.add(id);
                                            }
                                        }
                                    } while (nextPermutation(charInsertD));
                                }
                            } while (nextPermutation(charInsertN));
                        }
                    }
                }
            }
            System.out.println(sumN + " " + sumD);
        }
    }
}