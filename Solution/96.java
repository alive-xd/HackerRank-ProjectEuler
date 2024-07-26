import java.util.Scanner;

public class Solution {
    
    private static final int EMPTY = 0;
    
    private static boolean solve(int[][] board) {
        for(int y = 0; y < 9; y++) {
            for(int x = 0; x < 9; x++) {
                if(board[x][y] == EMPTY) {
                    boolean[] available = new boolean[10];
                    for(int i = 1; i < available.length; i++) {
                        available[i] = true;
                    }
                    for(int i = 0; i < 9; i++) {
                        if(board[i][y] != EMPTY) {
                            available[board[i][y]] = false;
                        }
                        if(board[x][i] != EMPTY) {
                            available[board[x][i]] = false;
                        }
                    }
                    int rx = (x / 3) * 3;
                    int ry = (y / 3) * 3;
                    for(int i = 0; i < 3; i++) {
                        for(int j = 0; j < 3; j++) {
                            if(board[i + rx][j + ry] != EMPTY) {
                                available[board[i + rx][j + ry]] = false;
                            }
                        }
                    }
                    for(int i = 1; i <= 9; i++) {
                        if(available[i]) {
                            board[x][y] = i;
                            if(solve(board)) {
                                return true;
                            }
                        }
                    }
                    board[x][y] = EMPTY;
                    return false;
                }
            }
        }
        return true;
    }
    
    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)) {
            int[][] board = new int[9][9];
            for(int y = 0; y < 9; y++) {
                char[] data = sc.nextLine().toCharArray();
                for(int x = 0; x < 9; x++) {
                    board[x][y] = data[x] - '0';
                }
            }
            solve(board);
            for(int y = 0; y < 9; y++) {
                for(int x = 0; x < 9; x++) {
                    System.out.print(board[x][y]);
                }
                System.out.println();
            }
        }
    }
}
