import java.util.List;
import java.util.ArrayList;

public class Assignment {
	
	String assignmentName;

	List<AssignmentResult> assignmentResultList = new ArrayList<AssignmentResult>();
	

	int averageScore;

	int  numberOfAGradesForFreshmen;
	int  numberOfAGradesForSenior;
	int  numberOfAGradesForSophomore;
	int  numberOfAGradesForJunior;
	

	int numberOfBGradesForFreshmen;
	int numberOfBGradesForSophomore;
	int numberOfBGradesForSenior;
	int numberOfBGradesForJunior;//(Freshmen, Sophomore, Junior, Senior)

	int numberOfCGradesForSophomore;
	int numberOfCGradesForSenior;
	int numberOfCGradesForJunior;
	int numberOfCGradesForFreshmen;//(Freshmen, Sophomore, Junior, Senior)

	int numberOfDGradesForSophomore;
	int numberOfDGradesForSenior;
	int numberOfDGradesForJunior;
	int numberOfDGradesForFreshmen;
	
	int numberOfFGradesForSophomore;
	int numberOfFGradesForSenior;
	int numberOfFGradesForJunior;
	int numberOfFGradesForFreshmen;//(Freshmen, Sophomore, Junior, Senior)

	
	public Assignment() {}
	
	
	public Assignment(String assignmentName) {
		this.assignmentName = assignmentName;
	}
	public void printAll() {
		System.out.println("Assignment name: " + assignmentName);
		System.out.println("Number of students: "+ assignmentResultList.size());
		System.out.println("Average score: " +  averageScore);
		System.out.println("Total number of As: " + numberOfAGradesForEachOf);
		System.out.println("Total number of Bs: " + numberOfBGradesForEachOf);
		System.out.println("Total number of Cs: " + numberOfCGradesForEachOf);
		System.out.println("Total number of Ds: " + numberOfDGradesForEachOf);
		System.out.println("Total number of Fs: " + numberOfFGradesForEachOf);
	}
	
}
