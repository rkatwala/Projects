package learnstuff;

public class fnfnf {
	static String phrase= "a cat ate late";
	public static void main(String[] args) {
	System.out.print(find("at"));
		
	}
	/*private int first, second;


public fnfnf(int a, int b) {
	first =a;
	second =b;
}

public String getProblem() {
	return first + "TIMES" + second;
}
public void nextProblem() {
	getProblem(first, second+1);

*/

	
	public static int find(String str) {
	for (int i=phrase.length(); i>0; i--) {
		if(phrase.substring(i-(1+str.length()), i-1).equals(str)){
		return (i-(1+str.length()));
	}
		
		
	}
	return -1;
	}
}
