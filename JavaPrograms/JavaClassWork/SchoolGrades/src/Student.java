import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.ThreadLocalRandom;

public class Student {
	
	static int studentNumber=0;
	
	 String name;
	 String classLevel;
	 int age;
	 int studentID;
	 List<AssignmentResult> assignmentResultsList = new ArrayList<AssignmentResult>();

	 
	public Student() {
		
		
		
	}
	 
	 public Student(String firstName, String lastName, String classLevel, int age) {
		 this.name = firstName + lastName;
		 this.classLevel = classLevel;
		 this.age= age;
		 studentID =  generateIDNumber();
	 }
	
	public int generateIDNumber() {
		studentNumber++;
		return studentNumber + 1000000;
		
		
		
	}
	
	
	public void printAll() {
		System.out.println("Student name: "+ name);
		System.out.println("Student classlevel: "+ classLevel);
		System.out.println("Student name: "+ name);
	}
	
	
	
}
