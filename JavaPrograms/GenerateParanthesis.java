import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Solution {
    
    private void solve(int cnt1, int cnt2, int n, List<String> ans, StringBuilder op, int ind) {
        if (ind >= n * 2) {
            ans.add(op.toString());
            return;
        }
        if (cnt1 < n && ind < n * 2 - 1) {
            op.append('(');
            solve(cnt1 + 1, cnt2, n, ans, op, ind + 1);
            op.deleteCharAt(op.length() - 1);
        }

        if (cnt2 < cnt1 && ind > 0) {
            op.append(')');
            solve(cnt1, cnt2 + 1, n, ans, op, ind + 1);
            op.deleteCharAt(op.length() - 1);
        }
    }

    public List<String> generateParenthesis(int n) {
        StringBuilder op = new StringBuilder();
        List<String> ans = new ArrayList<>();
        solve(0, 0, n, ans, op, 0);
        return ans;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the value of n:");
        int n = scanner.nextInt();

        Solution solution = new Solution();
        List<String> result = solution.generateParenthesis(n);
        
        System.out.println("Generated Parenthesis:");
        for (String combination : result) {
            System.out.println(combination);
        }

        scanner.close();
    }
}

