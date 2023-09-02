import java.util.Scanner;
import java.util.Arrays;

public class Solution {

    public void nextPermutation(int[] nums) {
        int n = nums.length, k, l;
        for (k = n - 2; k >= 0; k--) {
            if (nums[k] < nums[k + 1]) {
                break;
            }
        }
        if (k < 0) {
            reverse(nums, 0, n - 1);
        } else {
            for (l = n - 1; l > k; l--) {
                if (nums[l] > nums[k]) {
                    break;
                }
            }
            swap(nums, k, l);
            reverse(nums, k + 1, n - 1);
        }
    }
    
    private void reverse(int[] nums, int start, int end) {
        while (start < end) {
            swap(nums, start++, end--);
        }
    }
    
    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of elements: ");
        int n = scanner.nextInt();

        int[] nums = new int[n];
        System.out.println("Enter the elements:");
        for (int i = 0; i < n; i++) {
            nums[i] = scanner.nextInt();
        }

        Solution solution = new Solution();
        solution.nextPermutation(nums);

        System.out.println("Next permutation:");
        for (int num : nums) {
            System.out.print(num + " ");
        }
        System.out.println();

        scanner.close();
    }
}

