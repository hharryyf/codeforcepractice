#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
using namespace std;
pair<pair<int, int>, int> a[4000011];
struct myqueue {
	   int l = 0, r = -1;
	   
	   
	   void clear() {
	   		l = 0, r = -1;
	   }
	   
	   bool empty() {
	   		return l > r;
	   }	
	   
	   void push(pair<pair<int, int>, int> e) {
	   		a[++r] = e;
	   }   
	   
	   pair<pair<int, int>, int> front() {
			return a[l];
	   }
	   
	   void pop() {
	   		l++;
	   }
};

myqueue q;
vector<vector<bool> > grid;
int n, m;
int target = 0;
vector<vector<bool> > visited;
vector<vector<bool> > visited2;
int dx[8] = {1,1,1,0,0,-1,-1,-1};
int dy[8] = {1,0,-1,1,-1,1,0,-1};
bool flag = false;

bool valid(int T) {
	 int rem = target;
	 int N = n + 2, M = m + 2;
	 
	 int i, j;
	 q.clear();
	 for (i = 0 ; i < N; ++i) {
	 	 for (j = 0 ; j < M; ++j) {
		 	 if (!grid[i][j])  {
 				  visited[i][j] = true;
				  q.push(make_pair(make_pair(i, j), 0));
	  		 } else {
			      visited[i][j] = false;  
		     }
		     visited2[i][j] = false;
         }
	 }
	 
	 while (!q.empty()) {
	 	   auto p = q.front();
	 	   q.pop();
	 	   if (p.second >= T) break;
	 	   for (i = 0 ; i < 8; i++) {
		   	   int tx = p.first.first + dx[i], ty = p.first.second + dy[i];
			   if (tx >= 0 && tx < N && ty >= 0 && ty < M && !visited[tx][ty]) {
			   	  visited[tx][ty] = true;
			   	  q.push(make_pair(make_pair(tx, ty), p.second + 1));
			   	  rem--;
			   }	
		   }
	 }
	 
	 if (flag) return true;
	 if (rem == 0) return false;
	 q.clear();
	 for (i = 1; i <= n; ++i) {
	 	 for (j = 1; j <= m; ++j) {
		 	 if (!visited[i][j]) {
			   visited2[i][j] = true;
			   q.push(make_pair(make_pair(i, j), 0));
		     } 
         }
	 }
	 
	  while (!q.empty()) {
	 	   auto p = q.front();
	 	   q.pop();
	 	   if (p.second >= T) break;
	 	   for (i = 0 ; i < 8; ++i) {
		   	   int tx = p.first.first + dx[i], ty = p.first.second + dy[i];
			   if (tx >= 0 && tx < N && ty >= 0 && ty < M && !visited2[tx][ty]) {
			   	  visited2[tx][ty] = true;
			   	  q.push(make_pair(make_pair(tx, ty), p.second + 1));
			   	  rem++;
			   }	
		   }
	 }
	 return rem == target;
}

char s[1000011];

int main() {
	scanf("%d%d", &n, &m);
	grid = vector<vector<bool> >(n + 2, vector<bool>(m + 2, false));	
	visited = vector<vector<bool> >(n+2, vector<bool>(m+2, false));
	visited2 = vector<vector<bool> >(n+2, vector<bool>(m+2, false));
	int i, j;
	for (i = 1; i <= n; ++i) {
		scanf("%s", s);
		for (j = 0 ; j < m; ++j) {
			if (s[j] == 'X') { 
			   grid[i][j+1] = true;
		       target++;
            } 
		}
	}
	
	int low = 0, high = n * m + 1;
	int ans = 0;
	while (low <= high) {
		  int mid = (low + high) >> 1;
		  if (valid(mid)) {
		  	 ans = mid;
		  	 low = mid + 1;
		  } else {
		  	 high = mid - 1;
		  }
	}
	flag = true;
	valid(ans);
	printf("%d\n", ans);
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			if (!visited[i][j]) {
			   putchar('X');
			} else {
			   putchar('.');
			}
		}
		putchar('\n');
	}
	return 0;
}
