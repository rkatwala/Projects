package recursion;

public class count8 {
	public static int count8(int n) {
		if (n<10 & n!=8){
		return 0;
		}
		
		else if (n%10==8 & ((n/10)%10==8)){
			return 3+ count8((n/100));
		}
		else if (n%10==8){
			return 1+ count8(n/10);
			}
		else {
			return 0+ count8(n/10);
		}
	}
	public static void main(String[] args) {
		System.out.print(count8(8));
	}
}
