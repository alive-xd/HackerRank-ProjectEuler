import java.util.*;

public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int[][] grid = new int[20][20];
        for (int grid_i = 0; grid_i < 20; grid_i++) {
            for (int grid_j = 0; grid_j < 20; grid_j++) {
                grid[grid_i][grid_j] = in .nextInt();
            }
        }

        long max = 0;
        for (int k = 0; k < 17; k++) {
            for (int l = 0; l < 17; l++) {
                long temp = find_max(k, l, grid);
                if (temp > max) {
                    max = temp;
                }
            }
        }
        System.out.println(max);
    }

    public static long find_max(int x, int y, int[][] arr1) {

        long max = 0;
        long[] arr = new long[10];

        arr[0] = (long)(arr1[x][y] * arr1[x + 1][y] * arr1[x + 2][y] * arr1[x + 3][y]);
        arr[1] = (long)(arr1[x][y + 1] * arr1[x + 1][y + 1] * arr1[x + 2][y + 1] * arr1[x + 3][y + 1]);
        arr[2] = (long)(arr1[x][y + 2] * arr1[x + 1][y + 2] * arr1[x + 2][y + 2] * arr1[x + 3][y + 2]);
        arr[3] = (long)(arr1[x][y + 3] * arr1[x + 1][y + 3] * arr1[x + 2][y + 3] * arr1[x + 3][y + 3]);
        arr[4] = (long)(arr1[x][y] * arr1[x][y + 1] * arr1[x][y + 2] * arr1[x][y + 3]);
        arr[5] = (long)(arr1[x + 1][y] * arr1[x + 1][y + 1] * arr1[x + 1][y + 2] * arr1[x + 1][y + 3]);
        arr[6] = (long)(arr1[x + 2][y] * arr1[x + 2][y + 1] * arr1[x + 2][y + 2] * arr1[x + 2][y + 3]);
        arr[7] = (long)(arr1[x + 3][y] * arr1[x + 3][y + 1] * arr1[x + 3][y + 2] * arr1[x + 3][y + 3]);
        arr[8] = (long)(arr1[x][y] * arr1[x + 1][y + 1] * arr1[x + 2][y + 2] * arr1[x + 3][y + 3]);
        arr[9] = (long)(arr1[x][y + 3] * arr1[x + 1][y + 2] * arr1[x + 2][y + 1] * arr1[x + 3][y]);

        max = arr[0];
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;

    }
}