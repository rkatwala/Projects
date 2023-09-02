import java.util.*;
public class LineEquation {
	public static void main(String[] args) {
	Scanner penn = new Scanner (System.in);	
	
	String a,c;
	double d,e,f,g,h,i,j;
	
	System.out.println("What is your name?");
	a = penn.nextLine();
	
	System.out.println("what year are you in?");
	c = penn.next();
	penn.nextLine();
	
	System.out.println("what is your first x coordinate");
	d = penn.nextDouble();
	penn.nextLine();
	
	System.out.println("what is your first y coordinate");
	e = penn.nextDouble();
	penn.nextLine();
	
	System.out.println("what is your second x coordinate");
	f = penn.nextDouble();
	penn.nextLine();
	
	System.out.println("what is your second y coordinate");
	g = penn.nextDouble();
	penn.nextLine();
	
	h= (g-e)/(f-d);

	
	System.out.println("Okay " + a + " the " + c + ", the equation of your line is y="+ h +"x" + " + " +((-1*h*d) + e));
	
		
	
	
	
	
	

	}
	

}
