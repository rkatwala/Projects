import java.util.Scanner;

public class Solution {

    public int divide(int A, int B) {
        if (A == 1 << 31 && B == -1) return (1 << 31) - 1;
        int a = Math.abs(A), b = Math.abs(B), res = 0, x = 0;
        while (a - b >= 0) {
            for (x = 0; a - (b << x << 1) >= 0; x++);
            res += 1 << x;
            a -= b << x;
        }
        return (A > 0) == (B > 0) ? res : -res;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the value of A: ");
        int A = scanner.nextInt();
        
        System.out.print("Enter the value of B: ");
        int B = scanner.nextInt();
        
        Solution solution = new Solution();
        int result = solution.divide(A, B);
        
        System.out.println("Result of the division: " + result);

        scanner.close();
    }
}

