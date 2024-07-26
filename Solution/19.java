import java.util.*;

public class Solution {

    private static int SUNDAY = 0;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in .nextInt();
        while (t-- > 0) {
            // input
            long[][] dateArray = new long[2][3];
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 3; j++) {
                    dateArray[i][j] = in .nextLong();
                }
            }
            // begin
            adjust(dateArray);
            //
            long ak = 0;
            while (true) {
                if (dateArray[0][2] == 1) {
                    if (verify(dateArray[0][0], dateArray[0][1], dateArray[0][2])) {
                        ak++;
                    }
                }
                // set date
                dateArray[0][2] = 1;
                // month plus 1
                dateArray[0][1]++;
                if (dateArray[0][1] > 12) {
                    dateArray[0][1] = 1;
                    dateArray[0][0]++;
                }
                if (overDate(dateArray)) {
                    break;
                }
            }
            System.out.println(ak);
        } in .close();
    }

    /**
     * check if dateArray[0] is later than dateArray[1]
     * @param dateArray
     * @return
     */
    private static boolean overDate(long[][] dateArray) {
        if (dateArray[0][0] > dateArray[1][0]) {
            return true;
        } else if (dateArray[0][0] == dateArray[1][0]) {
            if (dateArray[0][1] > dateArray[1][1]) {
                return true;
            } else if (dateArray[0][1] == dateArray[1][1]) {
                if (dateArray[0][2] > dateArray[1][2])
                    return true;
            }
        }
        return false;
    }

    /**
     * let a[0] be earlier than a[1]
     * @param dateArray
     */
    private static void adjust(long[][] dateArray) {
        if (overDate(dateArray)) {
            exchange(dateArray);
        }
    }

    /**
     * exchange two input date
     * @param dateArray
     */
    private static void exchange(long[][] dateArray) {
        long[] tmp = new long[3];
        tmp = dateArray[1];
        dateArray[1] = dateArray[0];
        dateArray[0] = tmp;
    }

    private static boolean verify(long year, long month, long day) {
        // w=(y + (y / 4) + (c / 4) - (2 * c) + ((26 * (month + 1)) / 10) + day - 1) % 7
        //        long sourceY = year;
        //        long sourceM = month;
        if (month < 3) {
            month += 12;
            year -= 1;
        }
        long c = year / 100;
        long y = year % 100;
        int w = (int)((y + (y / 4) + (c / 4) - (2 * c) + ((26 * (month + 1)) / 10) + day - 1) % 7);
        boolean t = w == SUNDAY;
        //        if (t) {
        //            System.out.println(sourceY  + "-" + sourceM + "-" + day);
        //        }
        return t;
    }
}