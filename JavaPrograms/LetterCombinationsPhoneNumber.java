import java.util.*;
import java.util.List;

public class Solution {
    private List<String> ans = new ArrayList<>();
    private Map<Character, String> mp = new HashMap<>();

    public Solution() {
        mp.put('2', "abc");
        mp.put('3', "def");
        mp.put('4', "ghi");
        mp.put('5', "jkl");
        mp.put('6', "mno");
        mp.put('7', "pqrs");
        mp.put('8', "tuv");
        mp.put('9', "wxyz");
    }

    public List<String> letterCombinations(String digits) {
        return letterCombinations(digits, "");
    }

    private List<String> letterCombinations(String digits, String str) {
        if(digits.length() == 0) {
            if(!str.isEmpty()) {
                ans.add(str);
            }
            return ans;
        }
        
        char c = digits.charAt(0);
        String mappedChars = mp.get(c);
        for(char x : mappedChars.toCharArray()) {
            letterCombinations(digits.substring(1), str + x);
        }

        return ans;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the digit string:");
        String digits = sc.nextLine();

        Solution solution = new Solution();
        List<String> result = solution.letterCombinations(digits);
        
        System.out.println("Letter combinations are:");
        for(String combination : result) {
            System.out.println(combination);
        }

        sc.close();
    }
}

