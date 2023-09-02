package fibonacci;
import java.util.*;
public class fibonacci {

	public static void main(String[] args) {
		Scanner penn = new Scanner (System.in);
		
		long n,second,first,temp;
		
		System.out.println("what number of the sequence do you want");
		n = penn.nextLong();
		penn.nextLine();
		
		
		second = 1;
		first=0;
		temp=0;
		
		if (n == 1) {
			System.out.print(first);
		}
		else {
			System.out.print(first +" "+ second+" ");
			
			while (n>=3) {
				System.out.print((first+second) + " ");
			temp = first;
			first = second;
			second=temp+second;
			n--;
			
			}
		}
		
		
		
	}
	
}
