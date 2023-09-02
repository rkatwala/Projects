import java.util.ArrayList;
import java.util.Scanner;
public class sauce
{ 
  public static void main( String[] args)
  {
	  human self= new human("Sunny");
	  
	  sock left= new sock();
	  sock right= new sock();
	  
	  shoe x= new shoe("Nike", 11, "Black", left, right);
	  
	  shoeshelf y= new shoeshelf();
	  y.addshoe(x);
	  
	  System.out.println(self);
  }
}
