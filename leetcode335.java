import java.io.*;
import java.util.*;

/*
	This code implements the solution to 
	https://leetcode.com/problems/self-crossing/
	This problem is a mathematical problem, and since there is a constrains that
	all the array elements are positive by drawing out some possible
	crossings, we can see that only the previous segments could intersects with 
	the current segment, hence we only need to record the last 6 segments in a
	linked-list, the reason we use a linked-list is that it supports both remove
	front and remove back operation, and also traversal operation.
	Finally the segments are recorded by its endpoints.
*/

class Solution {
    public boolean isSelfCrossing(int[] path) {
		if (path == null || path.length <= 3) return false;        
		LinkedList<ParallelSegment> list = new LinkedList<ParallelSegment>();
		int x = 0, y = 0;
		ParallelSegment s;
		for (int i = 0 ; i < path.length; i++) {	
			if (i % 4 == 0) {
				s = new ParallelSegment(x, y, x, y + path[i]);
				y = y + path[i];
			} else if (i % 4 == 1) {
				s = new ParallelSegment(x, y, x - path[i], y);
				x = x - path[i];
			} else if (i % 4 == 2) {
				s = new ParallelSegment(x, y, x, y - path[i]);
				y = y - path[i];
			} else {
				s = new ParallelSegment(x, y, x + path[i], y);
				x = x + path[i];
			}
			
			if (s != null) {
				for (ParallelSegment ps : list) {
					if (ps != list.getLast() && s.intersect(ps)) {
						System.out.println(s + " " + ps);
						return true;
					}
				}
				
				list.add(s);
				
				if (list.size() >= 6) {
					list.removeFirst();
				}
			}
		}   	
		
		return false;
    }
}


class ParallelSegment {
	private int x1;
	private int y1;
	private int x2;
	private int y2;
	private boolean Horizontal;
	private boolean Vertical;
	// default constructor
	public ParallelSegment() {
	
	}
	// segment's endpoints
	public ParallelSegment(int x1, int y1, int x2, int y2) {
		this.x1 = x1;
		this.x2 = x2;
		this.y1 = y1;
		this.y2 = y2;
		if (this.y1 == this.y2) {
			this.Horizontal = true;
		} else {
			this.Horizontal = false;
		}
		
		if (this.x1 == this.x2) {
			this.Vertical = true;
		} else {
			this.Vertical = false;
		}
	}
	
	public boolean intersect(ParallelSegment other) {
		if (other == null) return false;
		if (this.isHorizontal()) {
			// horizontal line intersects with a vertical line
			if (other.isVertical()) {
				int x = other.getx1(), y = this.gety1();
				if (x <= Math.max(this.getx1(), this.getx2()) 
					&& x >= Math.min(this.getx1(), this.getx2())
					&& y <= Math.max(other.gety1(), other.gety2())
					&& y >= Math.min(other.gety1(), other.gety2())) {
					return true;	
				} 
			}
			
			// horizotal lines intersects
			if (other.isHorizontal() && this.gety1() == other.gety1()) {
				if (this.getx1() <= Math.max(other.getx1(), other.getx2()) 
					&& this.getx1() >= Math.min(other.getx1(), other.getx2())) {
					return true;	
				}
				
				if (this.getx2() <= Math.max(other.getx1(), other.getx2()) 
					&& this.getx2() >= Math.min(other.getx1(), other.getx2())) {
					return true;	
				}
			}
		} 
		// symmetric case, deal with vertical line and horizontal line
		if (this.isVertical()) {
			if (other.isHorizontal()) {
				int x = this.getx1(), y = other.gety1();
				if (x <= Math.max(other.getx1(), other.getx2()) 
					&& x >= Math.min(other.getx1(), other.getx2())
					&& y <= Math.max(this.gety1(), this.gety2())
					&& y >= Math.min(this.gety1(), this.gety2())) {
					return true;	
				} 
			}
			// vertical line and vertical line
			if (other.isVertical() && this.getx1() == other.getx1()) {
				if (this.gety1() <= Math.max(other.gety1(), other.gety2()) 
					&& this.gety1() >= Math.min(other.gety1(), other.gety2())) {
					return true;	
				}
				
				if (this.gety2() <= Math.max(other.gety1(), other.gety2()) 
					&& this.gety2() >= Math.min(other.gety1(), other.gety2())) {
					return true;	
				}
			}
		}
		
		return false;
	}
	
	public boolean isHorizontal() {
		return this.Horizontal;
	}
	
	public boolean isVertical() {
		return this.Vertical;
	}
	
	public int getx1() {
		return this.x1;
	}
	
	public int getx2() {
		return this.x2;
	}
	
	public int gety1() {
		return this.y1;
	}
	
	public int gety2() {
		return this.y2;
	}
	
	public String toString() {
		return "(" + this.x1 + " ," + this.y1 + ") -> " 
			   + "(" + this.x2 + " ," + this.y2 + ")";
	}
}


public class leetcode335 {
	public static void main(String[] args) {
		ArrayList<Integer> input = new ArrayList<Integer>();
		Scanner sc = new Scanner(System.in);
		while (sc.hasNext()) {
			input.add(sc.nextInt());
		}
		
		int[] arr = new int[input.size()];
		for (int i = 0 ; i < input.size(); i++) {
			arr[i] = input.get(i);
		}
		
		Solution s = new Solution();
		System.out.println("The path intersects itself is " + s.isSelfCrossing(arr));
	}
}
