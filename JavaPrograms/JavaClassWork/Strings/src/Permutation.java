import java.util.HashMap;

import java.util.Map;

public class Permutation {
	public static void main(String[] args){
		String string1 = "elephant";
		String string2 = "tanhplee";
		
		char[] test = string1.toCharArray();
		char[] test2 = string2.toCharArray();
		
		System.out.println(isPermutationHash(test, test2));
		
		
	}
	
	public static boolean isPermutation(char[] string1, char[] string2) {
		
		if(string1.length != string2.length){
			return false;
		}
		
		for(int i=0; i < string1.length; i++) {
			char currentChar = string1[i];
			
			for(int j=0; j<string2.length; j++) {
				
				if(currentChar == string2[j]) {
					string2[j]= '*';
					break;
				}
				
				if(j== string2.length-1) {
					
					return false;
				}
			}
		}
		
		return true;
	}

	
	public static boolean isPermutationHash(char[] string1, char[] string2) {
		
		if(string1.length != string2.length){
			return false;
		}
		
		Map<Character, Integer>  map1 = new HashMap<Character, Integer>();
		Map<Character, Integer>  map2 = new HashMap<Character, Integer>();
		for(int i = 0;i < string1.length; i++) {
			if (!map1.containsKey(string1[i])) {
				map1.put(string1[i], 1);
				continue;
			}
			
			map1.put(string1[i], map1.get(string1[i])+1);
			
		}
		
		for(int i=0; i< string2.length; i++) {
			if (!map2.containsKey(string2[i])) {
				map2.put(string2[i], 1);
				continue;
			}
			map2.put(string2[i], map2.get(string2[i]) + 1);
			
		}
		
		for(int i=0; i < string1.length; i++) {
			if(map1.get(string1[i])!= map2.get(string1[i])) {
				return false;
			}
		}
		
		
		return true;
	}
	
	
}
