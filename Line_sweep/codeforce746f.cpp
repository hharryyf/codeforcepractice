#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

int a[MAX_SIZE], b[MAX_SIZE];

struct song {
    int t;
	int id;
	bool operator < (song other) const {
	    if (t != other.t) return t < other.t;
	    return id < other.id;
	}
};

struct oriSet {
	int tol = 0;
	int len = 0;
	set<song> s;
	bool empty() {
		 return s.empty();	 
	}
	
	int size() {
	     return s.size();
	}
 	
	void insert(int id) {
		 s.insert(song{a[id], id});
		 tol += b[id];
		 len += a[id];
	}
	
	int extractmin() {
	    if (!s.empty()) {
	       return s.begin()->id; 
	    }
	    return -1;    
	}
	
	int extractmax() {
	    if (!s.empty()) {
	        return s.rbegin()->id;
	    }
	    return -1;
	}
	
	void del(int id) {
	    if (s.find(song{a[id], id}) != s.end()) {
	        s.erase(song{a[id], id});
	        tol -= b[id];
	        len -= a[id];
	    }
	}
};

struct lessSet {
	int tol = 0;
	int len = 0;
	set<song> s;
	bool empty() {
		 return s.empty();	 
	}
	
	int size() {
	    return s.size();
	}
	
	void insert(int id) {
		 int ti = a[id] - a[id] / 2;
		 s.insert(song{a[id], id});
		 tol += b[id];
		 len += ti;
	}
	
	int extractmin() {
	    if (!s.empty()) {
	       return s.begin()->id; 
	    }
	    return -1;    
	}
	
	int extractmax() {
	    if (!s.empty()) {
	        return s.rbegin()->id;
	    }
	    return -1;
	}
	
	void del(int id) {
	    if (s.find(song{a[id], id}) != s.end()) {
	        s.erase(song{a[id], id});
	        tol -= b[id];
	        len -= a[id] - a[id] / 2;
	    }
	}
};

oriSet s1;
lessSet s2;
int n, w, k;
// the s1 and s2 are called imbalance iff a[s1.extractmax()] > a[s2.extractmin()]
// or s2 isn't full and s1 isn't empty
void make_balance() {
    while (s2.size() < w && !s1.empty()) {
        int id = s1.extractmax();
        s1.del(id);
        s2.insert(id);
    }
    
    while (!s1.empty() && s2.size() == w) {
        int id1 = s1.extractmax(), id2 = s2.extractmin();
        if (a[id1] <= a[id2]) break;
        if (a[id1] > a[id2]) {
            s1.del(id1);
            s2.del(id2);
            s1.insert(id2);
            s2.insert(id1);
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &w, &k);
    int i, j, ans = 0;
    for (i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }
    
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (i = 1, j = 1; i <= n; i++) {
        s1.insert(i);
        make_balance();
        while (j <= i && s1.len + s2.len > k) {
            s1.del(j);
            s2.del(j);
            make_balance();
            j++;
        }
        ans = max(ans, s1.tol + s2.tol);
    }
    
    printf("%d\n", ans);
	return 0;
}

