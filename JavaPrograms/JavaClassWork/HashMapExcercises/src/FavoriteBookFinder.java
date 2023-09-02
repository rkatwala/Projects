import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.*;
import java.io.File;

public class FavoriteBookFinder {

	
	
	
	public static void main(String[] args){
		List<String> bookList = createAllBookList("Data.txt");
		List<String> aliceList = createFavoriteBookListForAlice(bookList);
   	 	List<String> alexList = createFavoriteBookListForAlex(bookList);
   	    List<String> smithList = createFavoriteBookListForSmith(bookList);
   	    
   	    printAll(aliceList, alexList, smithList);
   	    

		
	}
	
	
	public static ArrayList<String> createAllBookList(String fileName){
		try{
	    	File file = new File(fileName);
	   		Scanner reader = new Scanner(file);
	   		List<String> bookList = new ArrayList<String>();
	    	String input;
	      	String tempString = "";
	   	 	while(reader.hasNext()){
	      		input = reader.nextLine();
	          	
	          	
	          	bookList.add(input);
	          
	          
	          
	    	}
	   	 	return (ArrayList<String>) bookList;
		}
		
		catch(Exception exception){
		     System.out.println(exception.getMessage());     
		}
		return null;
	}

	
	public static ArrayList<String>  createFavoriteBookListForAlice(List<String> bookList) {
		List<String> aliceList = new ArrayList<String>();
		
		for(int i=0;i<bookList.size(); i++) {
			String[] strings = bookList.get(i).split(" ");
			for(int j=0; j< strings.length; j++) {
				if (strings[j].equals("fun")) {
					aliceList.add(bookList.get(i));
					break;
				}
			}
		}
				
		
		return (ArrayList<String>) aliceList;
	}
	
	public static ArrayList<String>  createFavoriteBookListForAlex(List<String> bookList) {
		List<String> alexList = new ArrayList<String>();
		
			for(int i=0;i<bookList.size(); i++) {
				String[] strings = bookList.get(i).split(" ");
				if (strings.length == 1) {
					alexList.add(bookList.get(i));
					continue;
			}
		}
				
		
		return (ArrayList<String>) alexList;
		
	}
	
	public static ArrayList<String>  createFavoriteBookListForSmith(List<String> bookList) {
		List<String> smithList = new ArrayList<String>();
		
		for(int i=0;i<bookList.size(); i++) {
			String[] strings = bookList.get(i).split(" ");
			if (strings.length>=2) {
				smithList.add(bookList.get(i));
				continue;
		}
	}
			
	
		return (ArrayList<String>) smithList;
		
	}
	
	
	public static void printAll(List<String> aliceList, List<String> alexList, List<String> smithList) {
		
		Map <String, List<String>> personToFavoriteBookListMap = new HashMap<String, List<String>>();
		
		personToFavoriteBookListMap.put("Alice", aliceList);
		personToFavoriteBookListMap.put("Alex", alexList);
		personToFavoriteBookListMap.put("Smith", smithList);
			
		System.out.println(personToFavoriteBookListMap);
		/*
		
		System.out.print("Alices favorite books are: ");
		for(int i=0;i< aliceList.size();i++) {
			System.out.print(aliceList.get(i)+ "     ");
		}
		System.out.println();
		
		System.out.print("Alex favorite books are: ");
		for(int i=0;i< alexList.size();i++) {
			System.out.print(alexList.get(i)+ "     ");
		}
		System.out.println();
		
		System.out.print("Smith favorite books are: ");
		for(int i=0;i< smithList.size();i++) {
			System.out.print(smithList.get(i)+ "    ");
		}
		System.out.println();
		*/
		
	}
	
}
