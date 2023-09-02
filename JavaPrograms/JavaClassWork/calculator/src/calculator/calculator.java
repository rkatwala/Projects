package calculator;
import java.util.Scanner;
public class calculator {

	public static void main (String[] args)
	{
		Scanner input = new Scanner(System.in);
		int command = 0;
		int first_number = 0;
		int second_number = 0;
		double after_command = 0;
		int remainder = 0;
		int proceed = 1;
			
		while (proceed == 1)
		{
			System.out.println("Enter 1. add, 2. subtract, 3. multiply, 4. divide");
			command = input.nextInt();
			input.nextLine();
			System.out.println("Enter the first number");
			first_number = input.nextInt();
			input.nextLine();
			System.out.println("Enter the second number");
			second_number = input.nextInt();
			input.nextLine();
			
			if (command == 1)
			{
				after_command = first_number + second_number;
			}
			else if (command == 2)
			{
				after_command = first_number - second_number;
			}		
			else if (command == 3)
			{
				after_command = first_number * second_number;
			}
			else if (command == 4)
			{
				after_command = first_number/second_number;
				remainder = first_number % second_number;
			}
			else
			{
				System.out.println("Invalid input");
			}
				
			if (remainder == 0)
			{
				System.out.println("Your answer is " + after_command);
			}
				
			else
			{
				System.out.println("Your answer is " + after_command + " remainder " + remainder);
			}
				
			System.out.println("Would you like to proceed again? 1. yes, 2. no)");
			proceed = input.nextInt();
			input.nextLine();
		}
			
	}

}

