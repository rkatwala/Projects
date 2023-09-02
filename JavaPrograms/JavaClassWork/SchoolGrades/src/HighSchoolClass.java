import java.util.*;
import java.io.*;
public class HighSchoolClass {

	String name;
	List<Assignment> assignmentList = new ArrayList<Assignment>();
	List<Student> students = new ArrayList<Student>();
	List<AssignmentResult> assignmentResults = new ArrayList<AssignmentResult>();
	Map<Integer, Student> studentMap = new HashMap<Integer, Student>();
	Map<String, Assignment> assignmentMap = new HashMap();
	
	public HighSchoolClass() {}
	
	public HighSchoolClass(String name) {
		this.name =name;
	}
	
	
	public void readStudentsFromFile() throws FileNotFoundException{
		File file= new File("Students");
		Scanner reader = new Scanner(file);
		
		
		while(reader.hasNext()) {
		
			String firstName;
			String lastName;
			String classLevel;
			int age;
		
			firstName = reader.next();
			lastName = reader.next();
			classLevel = reader.next();
			age = reader.nextInt();
		
			Student newStudent = new Student(firstName, lastName, classLevel, age);
			newStudent.printAll();
			students.add(newStudent);
		}
		
	}
	
	
	public void readAssignmentResultsFromFile() throws FileNotFoundException{
		File file  = new File("AssignmentResults");
		Scanner reader= new Scanner(file);
		
		while(reader.hasNext()) {
			int studentID = reader.nextInt();
			String assignmentNumber = reader.next();
			String classLevel= reader.next();
			
			AssignmentResult newAssignmentResult= new AssignmentResult(studentID, assignmentNumber, classLevel);
			assignmentResults.add(newAssignmentResult);
			
			
		}
			
		
	}
	
	public void storeAssignmentResultsInTheCorrectStudent() {
		
	//	Map<Integer, Student> studentMap = new HashMap();
		
		for(int i=0;i<students.size();i++) {
			studentMap.put(students.get(i).studentID, students.get(i));
			
		}
				
		for(int i=0; i<assignmentResults.size();i++) {
			if(studentMap.containsKey(assignmentResults.get(i).studentID)){
				Student temp = studentMap.get(assignmentResults.get(i).studentID);
				
				temp.assignmentResultsList.add(assignmentResults.get(i));
				
				//studentMap.get(assignmentResults.get(i).studentID).assignmentResultsList.add(assignmentResults.get(i));
				studentMap.put(assignmentResults.get(i).studentID, temp);
			}
		
			
		}
	}
	
	public void storeAssignmentResultsInTheCorrectAssignment() {
		

		for(int i=0;i<assignmentList.size();i++) {
			assignmentMap.put(assignmentList.get(i).assignmentName, assignmentList.get(i));
			
		}
				
		for(int i=0; i<assignmentResults.size();i++) {
			if(assignmentMap.containsKey(assignmentResults.get(i).assignmentNumber)){
				Assignment temp = assignmentMap.get(assignmentList.get(i).assignmentName);
				
				temp.assignmentResultList.add(assignmentResults.get(i));
				
				//studentMap.get(assignmentResults.get(i).studentID).assignmentResultsList.add(assignmentResults.get(i));
				assignmentMap.put(assignmentResults.get(i).assignmentNumber, temp);
			}
			
			
		}
		
		
	}
	
	public int computeStatisticForEveryAssignment() {
		return 0;
	}
	
	public void printStatisticForEveryAssignment() {
		
	}
	
	
	
	
	
}
