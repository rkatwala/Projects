
public class Palindrome {

	public static void main(String[] args){
		String test = "";
		System.out.println(isPalindrome(test));
	}
	
	
	public static boolean isPalindrome(String str) {
		char[] word = str.toCharArray();
		
		
		for(int i=0;i<str.length()/2;i++) {
			
			if (word[i] != word[str.length()-i-1]) {
				return false;
			}
		}
		
		return true;
		
	}
	
}
