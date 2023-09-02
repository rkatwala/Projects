// Rahul Katwala

import java.util.*;

public class atm {

	public static void main(String[] args) {
		// enter scanner class
		Scanner penn = new Scanner(System.in);
		// balance will be represented by a
		// ask user for the password which is 2018
		System.out.println("Please enter your password for your account: ");
		int a = penn.nextInt();

		if (a == 2018) {
			int bal = 1000;
			// the decision given will be represented by c
			// ask user for c
			System.out.println(
					" Would you like to deposit or withdraw or quick cash. Press 1 for deposit. Press 2 for Withdraw. Press 3 for Quickcash.");
			int c = penn.nextInt();
			if (c == 1) {
				// enter desposit method
				dep(10000);

			}
			if (c == 2) {
				// enter withdraw method
				wdraw(10000);

			}
			if (c == 3) {
				QC(20, 40, 60, 80);
			}
			// continue option will be represented by b
			// ask user for b

			System.out.println("Do you wish to continue. If you would like to press 1. If not, press 2.");
			int b = penn.nextInt();
			if (b == 1) {
				main(args);

			}
			if (b == 2) {
				System.out.println("Thank you and have a good day");

			}

		}
	}

	public static int dep(int cash1) {
		// enter scanner class
		Scanner penn = new Scanner(System.in);
		System.out.println("How much money will be deposited");
		// d will be represented for deposit

		int d = penn.nextInt();

		System.out.println("You now have " + (cash1 + d) + " dollars in your account");
		return d;

	}

	public static int wdraw(int cash2) {
		// enter scanner class
		Scanner penn = new Scanner(System.in);
		System.out.println("Enter the amount of money you would like to withdraw");
		int e = penn.nextInt();

		System.out.println("You have " + (cash2 - e) + " dollars in your account");

		return e;

	}

	public static int QC(int one, int two, int three, int four) {
		// entering scanner class
		Scanner penn = new Scanner(System.in);
		System.out.println(
				"Press 1 if you want 10 dollars. Press 2 if you want 20 dollars. Press 3 if you want 30 dollars. Press 4 if you want 100 dollars.");
		int choice = penn.nextInt();
		// if the choice is equal to 1 then print the following
		if (choice == 1) {
			System.out.println("You have " + (10000 + one) + " dollars in your account.");

		} else if (choice == 2) {
			// if the choice is equal to 2 then print the following
			System.out.println("You have " + (10000 + two) + " dollars in your account.");
			// if the choice is equal to 3 then print the following
		} else if (choice == 3) {

			System.out.println("You have " + (10000 + three) + " dollars in your account.");
			// if the choice is equal to 4 then print the following
		} else {
			System.out.println("You have " + (10000 + four) + " dollars in your account.");

		}
		return one;

	}

}
