import java.util.*;

class Solution {
	// we have a matrix which row is much greater than col
	// hence we can brute force all the start-end pair of cols
	// and find if there's a [row1, row2, col1, col2] matrix such that its
	// sum is no greater than k, for this we can use the lower_bound/floor
	// method to deal with, so in general the complexity would be 
	// col*col*row*log(row)
    public int maxSumSubmatrix(int[][] matrix, int upper) {
    	if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
    		return 0;
    	}
    	
    	int i, j, k;
    	int ans = Integer.MIN_VALUE;
    	int row = matrix.length;    
    	int col = matrix[0].length;
    	for (i = 0 ; i < col; i++) {
			int[] prefix = new int[row];    		
    		for (j = i; j < col; j++) {
				int current = 0;
    			TreeSet<Integer> set = new TreeSet<Integer>();
    			set.add(0);
    			for (k = 0 ; k < row; k++) {
					prefix[k] += matrix[k][j];    				
    				current = current + prefix[k];
    				Integer dest = set.ceiling(current - upper);
    				if (dest != null) {
    					ans = Math.max(ans, current - dest);
    				}
    				set.add(current);
    			}	
    		}
    	}
    	
    	return ans;
    }
}

public class leetcode363 {
	public static void main(String[] args) {
		int n, m, k;
		Scanner sc = new Scanner(System.in);
		// n rows and m cols
		n = sc.nextInt();
		m = sc.nextInt();
		k = sc.nextInt();
		int[][] matrix = new int[n][m];
		int i, j;
		for (i = 0 ; i < n; i++) {
			for (j = 0 ; j < m; j++) {
				matrix[i][j] = sc.nextInt();
			}
		}
		
		Solution s = new Solution();
		System.out.println("The maximum matrix sum no greater than " + k + " is " 
							+ s.maxSumSubmatrix(matrix, k));
	}
}
