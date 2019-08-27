#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#define MAX_LEN 200011
using namespace std;

bool valid(int n, int k, int diff);
/*
	This program implements https://codeforces.com/problemset/problem/1156/C
	We use the idea of binary search for answer, set the answer to be k
	and see whether the first k numbers could match with the last k numbers
	completely. If so we increment k, otherwise, we decrease k.
	
	Claim: For an increasing sequence of number with size n, suppose there's a 
		   match that is size k, then the match 
				num[0]->num[n-k]
				num[1]->num[n-k+1]
				num[2]->num[n-k+2]
					...
				num[k-1]->num[n-1]
			must be a valid match.
	Proof for the correctness of this algorithm:
			Suppose that there's a match of size k, and the above match is invalid.
			Then suppose that the valid match of size k is
			    num[a1]->num[ak+1]
			    num[a2]->num[ak+2]
			    num[a3]->num[ak+3]
			        ...
			    num[ak]->num[a2k]
			Then note that num[ak+1] to num[a2k] is non-decreasing, and num[a1]
			to num[ak] is non-decreasing, hence we can easily see that
			num[ai] >= num[i-1] and num[ak+i] <= num[n-k+i-1],
			therefore, we can see that for all pair if we change num[ai] to num[i-1]
			and num[ak+i] to num[n-k+i-1] the match is also valid.
			Hence a contradiction occur, thus 
				num[0]->num[n-k]
				num[1]->num[n-k+1]
				num[2]->num[n-k+2]
					...
				num[k-1]->num[n-1]
			must be a valid match.
	
*/

int arr[MAX_LEN];

int main(int argc, char *argv[]) {
	int n, i, z;
	scanf("%d%d", &n, &z);
	for (i = 0 ; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	
	
	sort(arr, arr+n);
	
	int low = 0, high = n / 2;
	int ans = 0;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (valid(n, mid, z)) {
			ans = max(ans, mid);
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	
	printf("%d\n", ans);
	return 0;
}

// see if num[0] to num[k-1] could make a match with num[n-k+1] to num[n-1]
bool valid(int n, int k, int diff) {
	if (k > n / 2) {
		return false;
	}	
	
	int low = 0;
	while (low < k) {
		if (arr[n - k + low] -arr[low] < diff) {
			return false;
		} 
		low++;
	}
	return true;
}
