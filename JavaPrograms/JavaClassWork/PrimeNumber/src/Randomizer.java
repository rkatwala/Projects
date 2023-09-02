import java.util.*;
import java.util.concurrent.ThreadLocalRandom;
public class Randomizer {

	public static void main(String[] args){
		//int test = 0; 
		List<Integer> listOfNumbers = new ArrayList<Integer>();
		listOfNumbers.add(0);
		listOfNumbers.add(6);
		listOfNumbers.add(7);
		listOfNumbers.add(8);
		listOfNumbers.add(9);
		for(int i=0;i<listOfNumbers.size();i++) {
			System.out.print(listOfNumbers.get(i));
		}
		List<Integer> remainingListOfNumberIndex = new ArrayList<Integer>();
		List<Integer> newListOfNumbers = new ArrayList<Integer>();
		
		for(int i=0;i<listOfNumbers.size();i++) {
			remainingListOfNumberIndex.add(i);
			newListOfNumbers.add(i);
		}
		System.out.println();
		//Random randomGenerator = new Random();
		int pos = 0;
		for(int i=0;i< listOfNumbers.size();i++) {
			int min=0;
			int max = remainingListOfNumberIndex.size();
			pos = ThreadLocalRandom.current().nextInt(min, max);
			System.out.print(i + " " + pos + " ");
			System.out.println(remainingListOfNumberIndex.get(pos));
			newListOfNumbers.set(remainingListOfNumberIndex.get(pos), listOfNumbers.get(i));
			remainingListOfNumberIndex.remove(pos);
			
		}
		
		for(int i=0;i<newListOfNumbers.size();i++) {
			System.out.print(newListOfNumbers.get(i));
		}
		

		
	}
	
}
