import java.util.concurrent.ThreadLocalRandom;
public class AssignmentResult {

	
	
	int studentID;
	String assignmentNumber;
	int score;
	String studentClassLevel;
	char grade;
	
	public  AssignmentResult() {
	}
	
	public AssignmentResult(int studentID, String assignmentNumber, String studentClassLevel) {
		this.studentID = studentID;
		this.assignmentNumber = assignmentNumber;
		this.studentClassLevel = studentClassLevel;
		score = generateRandomScore();
		grade = getGrade();
	}
	
	public int generateRandomScore() {
		int max=10;
		int min=1;
		int RandomNumber = ThreadLocalRandom.current().nextInt(min, max);
		
		if (RandomNumber!=1) {
			max=100;
			min=60;
			return ThreadLocalRandom.current().nextInt(min, max);
		}
		else {
			return 0;
		}
	}
	
	public char getGrade() {
		if(score<60) {
			return 'F';
		}
		else if(score<70) {
			return 'D';
			
		}
		else if(score<80) {
			return 'C';
		}
		else if(score<90) {
			return 'B';
			
		}
		
		else {
			return 'A';
		}
	}
	
	
	
}
