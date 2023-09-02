import java.util.Scanner;


public class MathFunctions {
	public static void main(String[] args){
		int test = 0; 
		Scanner reader = new Scanner(System.in);
		MathFunctions mathFunction = new MathFunctions();
		while(test!=-1) {
			System.out.println("Please enter a number: ");
			test = reader.nextInt();
			
			System.out.println(test + " is a prime number: " + mathFunction.isPrime(test));
		}
		
	}
	
	public boolean isPrime(int num) {
		
		if(num%2==0) {
			return false;
		}
		else {
			
	
		
			for(int i=3;i <= (int) Math.sqrt(num); i+=2) {
				if (num%i==0) {
					return false;
				}
			}
		}
		
		return true;
		
	}
	
	
	
	
	
	
}
