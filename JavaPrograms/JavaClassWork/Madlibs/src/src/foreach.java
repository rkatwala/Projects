package src;
//Rahul Katwala
public class foreach {

	public static void main(String[] args) {
	      int[] array = { 1,2,3,4};
	      foreach(array);
	   }
	
	public static void foreach(int[] data) {
	      
		
	      for (int a  : data) 
	      {
	         System.out.print(a+ " ");
	      }
	}

}