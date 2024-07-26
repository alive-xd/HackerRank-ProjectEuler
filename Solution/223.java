import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
		
        Scanner s = new Scanner(System.in);
        int Q = s.nextInt();
        List < Integer > triplet = new ArrayList < > ();
        triplet.add(17);
        for (int i = 0; i < Q; i++) {
            int n = s.nextInt();
            int a, b, c = 2;
            int lastNum = triplet.get(triplet.size() - 1);
            int waste = 0;
            int answer = 0;
            int ansind = 0;
            long time1 = Calendar.getInstance().getTimeInMillis();
            if (n > lastNum) {
                for (a = 2; a < n / 3; a++) {
                    b = a;
                    c = (int) Math.ceil(Math.sqrt(a * a + b * b - 1));
                    for (b = Math.max(a, ((lastNum) / 2) - a); b < (n - 1) / 2 && (c < a + b) &&
                        (a + b + c <= n); b++) {
                        waste++;
                        c = (int) Math.ceil(Math.sqrt(a * a + b * b - 1));
                        if (b == c)
                            break;
                        if (a + b + c <= lastNum)
                            continue;
                        if (a * a + b * b == c * c + 1) {
                            triplet.add(a + b + c);
                        }
                    }
                }
                Collections.sort(triplet);
            }

            if (n >= triplet.get(triplet.size() - 1)) {
                ansind = triplet.size();
            } else if (n > 17) {
                for (int j = 0; j < triplet.size(); j++) {
                    if (triplet.get(j) > n) {
                        ansind = j;
                        break;
                    }
                }

            }
            long time2 = Calendar.getInstance().getTimeInMillis();
            answer = ansind + (n - 1) / 2;
            System.out.println(answer);
        }
    }
}