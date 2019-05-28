import java.util.*;

class Solution {
    public boolean increasingTriplet(int[] nums) {
        long minone = Long.MAX_VALUE, 
            mintwo = Long.MAX_VALUE, 
            minthree = Long.MAX_VALUE;
        int i;
        for (i = 0; i < nums.length; i++) {
            if (i == 0) {
                minone = (long) nums[i];
            } else if (i == 1) {
                if ((long) nums[i] > minone) {
                    mintwo = Math.min(mintwo, (long) nums[i]);
                }
                minone = Math.min(minone, (long) nums[i]);
            } else {
                if ((long) nums[i] > mintwo) {
                    minthree = Math.min(minthree, (long) nums[i]);
                }
                if ((long) nums[i] > minone) {
                    mintwo = Math.min(mintwo, (long) nums[i]);
                }
                minone = Math.min(minone, (long) nums[i]);
            }
        }
        
        System.out.println("(" + minone + " ," + mintwo + " ," + minthree + ")");
        return (minthree != Long.MAX_VALUE); 
    }
}

public class leetcode334 {
	public static void main(String[] args) {
		Solution s = new Solution();
		int[] arr = new int[args.length];
		int i;
		for (i = 0 ; i < args.length; i++) {
			arr[i] = Integer.parseInt(args[i]);
		}
		
		System.out.println(s.increasingTriplet(arr));
	}
}
