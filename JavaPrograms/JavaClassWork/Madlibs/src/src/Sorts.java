// Rahul Katwala
package src;
import java.util.*;
public class Sorts {
	
	
		public static void main (String [] args) {
			Scanner penn = new Scanner(System.in);
			System.out.println("Enter five numbers numbers");
			int one = penn.nextInt();
			penn.nextLine();
			
			int two = penn.nextInt();
			penn.nextLine();
			
			int three = penn.nextInt();
			penn.nextLine();
			
			int four = penn.nextInt();
			penn.nextLine();
			
			int five = penn.nextInt();
			penn.nextLine();
			
			ArrayList<Integer> x = new ArrayList<Integer>(5);
			ArrayList<Integer> z = new ArrayList<Integer>(8);
			x.add(one);
			x.add(two);
			x.add(three);
			x.add(four);
			x.add(five);
			System.out.println("\nSelection  Sort");
			for (int zz = 0; zz < x.size(); zz++) {
				System.out.print(x.get(zz) + " ");
			}
			System.out.println();
			int max = 0;
			int max1 = 0;
			int while1 = 0;
			selectionsort(x, max, max1, while1);
			
			z.add(one);
			z.add(two);
			z.add(three);
			z.add(four);
			z.add(five);
			
			System.out.println("Enter a number to search for (linear)");
			int resp = penn.nextInt();
			penn.nextLine();
			int while2 = 0;
			linearsearch(z, resp, while2);
			
			System.out.println("Enter three more numbers in order keeping with the first five you entered");
			int six = penn.nextInt();
			penn.nextLine();
			
			int seven = penn.nextInt();
			penn.nextLine();
			
			int eight = penn.nextInt();
			penn.nextLine();
			
			x.add(six);
			x.add(seven);
			x.add(eight);
			
			System.out.println("Enter a number to search for (binary)");
			int resp1 = penn.nextInt();
			penn.nextLine();
			int while3 = 3;
			binarysearch(x, resp1,while3);
			
			
			
			int placeholder = 1;
			
			int[] actual = { 51, 11, 67, 23, 34};
		    mergeSort(actual, 5);
			
			
		}
		
		public static void selectionsort(ArrayList<Integer> x, int max, int max1, int while1) {
		
			if (while1 == x.size()) {
				System.out.println("");
			}
			
			else {
				
			
				for (int i = 0; i < x.size() - while1; i++) {
					if (x.get(i) > max){
						max = x.get(i);
						max1 = i;
					
					}
				
					if (i == x.size() - while1 - 1){
						x.remove(max1);
						x.add(4-while1,max);
					}
				}
			
				for (int z = 0; z < x.size(); z++){
					System.out.print(x.get(z) + " ");
				}
				while1++;
				max = 0;
				max1 = 0;
				System.out.println();
				selectionsort(x,max,max1,while1);
				
			}
			
		}
		
		public static void linearsearch(ArrayList<Integer> x, int resp, int while2){
			
			if (while2 == 4) {
				System.out.println("");
			}
			else {
			
				if (x.get(while2) == resp) {
					System.out.println("Found at position: " + while2);
					linearsearch(x, resp, 4);
				}
				else {
					while2++;
					if (while2 >= 4) {
						System.out.println("Item not found");
					}
					linearsearch(x, resp, while2);
				}
			}
		}
		
		public static void binarysearch(ArrayList<Integer>x, int resp1, int while3) {
			if (resp1 == x.get(while3)) {
				System.out.println("Item found at : " + while3);
			}
			
			else {
				if (resp1 < x.get(while3) && while3 == 3) {
					while3 -= 2;
					binarysearch(x,resp1,while3);
				}
				else if (resp1 > x.get(while3)&& while3 == 3) {
					while3 += 2;
					binarysearch(x,resp1,while3);
				}
				else if (resp1 > x.get(while3)) {
					while3++;
					binarysearch(x,resp1,while3);
				}
				else if (resp1 < x.get(while3)) {
					while3--;
					binarysearch(x,resp1,while3);
				}
			}
		
		}
		
		public static void mergeSort(int[] a, int n)  {
			for (int i = 0; i < a.length; i++) {
		    	System.out.print(a[i] + " ");
		    }
		    System.out.println();
		    if (n < 2) {
		        return;
		    }
		    int mid = n / 2;
		    int[] l = new int[mid];
		    int[] r = new int[n - mid];
		 
		    for (int i = 0; i < mid; i++) {
		        l[i] = a[i];
		    }
		    for (int i = mid; i < n; i++) {
		        r[i - mid] = a[i];
		    }
		    mergeSort(l, mid);
		    mergeSort(r, n - mid);
		 
		    merge(a, l, r, mid, n - mid);
		    for (int i = 0; i < a.length; i++) {
		    	System.out.print(a[i] + " ");
		    }
		    System.out.println();
		}
		
		public static void merge(int[] a, int[] l, int[] r, int left, int right)  {
				  
				    int i = 0, j = 0, k = 0;
				    while (i < left && j < right) {
				        if (l[i] <= r[j]) {
				            a[k++] = l[i++];
				        }
				        else {
				            a[k++] = r[j++];
				        }
				    }
				    while (i < left) {
				        a[k++] = l[i++];
				    }
				    while (j < right) {
				        a[k++] = r[j++];
				    }
		}
}
