#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

class myset {
public:
	void setsize(int n) {
		this->n = n;
	}
	
	int carin(int id) {
		int dist = 0, ret = 0;
		if (pt.empty()) {
			ret = 1;
			pt.insert(1);
			visited[id] = ret;
			return ret;
		}
		
		if (pt.find(1) == pt.end()) {
			int r = *pt.upper_bound(1);
			dist = r - 1;
			ret = 1;
		}
		
		if (pt.find(n) == pt.end()) {
			int l = *pt.rbegin();
			if (dist < n - l) {
				ret = n;
				dist = n - l;
			} 
		}
		
		if (!st.empty()) {
			car c = *st.begin();
			if (dist < (c.r - c.l) / 2 || ((dist <= (c.r - c.l) / 2) && ((c.l + c.r) / 2 < ret))) {
				ret = (c.l + c.r) / 2;
				dist = (c.r - c.l) / 2;
			}
		}
		
		if (ret == 1) {
			int r = *pt.upper_bound(ret);
			st.insert(car{ret, r});
			pt.insert(ret);
		} else if (ret == n) {
			int l = *pt.rbegin();
			st.insert(car{l, ret});
			pt.insert(ret);		
		} else {
			int r = *pt.upper_bound(ret);
			int l = *prev(pt.lower_bound(ret));
			pt.insert(ret);
			st.erase(st.find(car{l, r}));
			st.insert(car{l, ret});
			st.insert(car{ret, r});
		}
		visited[id] = ret;
		return ret;
	}

	void carout(int id) {
		if (st.empty()) {
			pt.erase(visited[id]);
		} else {
			int l = n + 1, r = 0;
			if (visited[id] > *pt.begin()) {
				l = *prev(pt.lower_bound(visited[id]));
				st.erase(st.find(car{l, visited[id]}));
			}
			
			if (visited[id] < *pt.rbegin()) {
				r = *pt.upper_bound(visited[id]);
				st.erase(st.find(car{visited[id], r}));
			}
			
			if (l <= r) {
				st.insert(car{l, r});
			}
		}
		
		pt.erase(visited[id]);
		visited[id] = 0;
	}

private:
	int visited[MAX_SIZE];
	
	struct car {
		int l, r;
		bool operator < (const car other) const {
			int distc = (r - l) / 2;
			int disto = (other.r - other.l) / 2;
			if (distc != disto) return distc > disto;
			return r < other.r;
		}
	};
	
	multiset<car> st;
	
	set<int> pt;
	
	int n;
};

myset s;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	s.setsize(n);
	int i;
	for (i = 1; i <= m; i++) {
		int tp, id;
		scanf("%d%d", &tp, &id);
		if (tp == 1) {
			printf("%d\n", s.carin(id));
		} else {
			s.carout(id);
		}
	}
	return 0;
}
