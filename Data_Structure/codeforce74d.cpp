#include <bits/stdc++.h>
#define MAX_SIZE 524292
using namespace std;

class BIT {
public:
    void setsize(int n) {
        this->n = n;
    }
    
    void update(int x, int val) {
        while (x <= n) {
            tree[x] += val;
            x += shift(x);
        }
    }
    
    int query(int l, int r) {
        if (l > r) return 0;
        return getans(r) - getans(l - 1);
    }
    
private:
    int tree[MAX_SIZE];
    int n;
    
    int shift(int x) {
        return x & (-x);
    }
    
    int getans(int x) {
        int ret = 0;
        while (x > 0) {
            ret += tree[x];
            x -= shift(x);
        }
        
        return ret;
    }
};

BIT tree;

struct seat {
    int l, r;
    bool operator < (const seat oth) const {
          if (r - l != oth.r - oth.l) return (r - l) > (oth.r - oth.l);
          return r > oth.r;
    }
};

set<seat> st;
map<int, seat> mp;
int n;
vector<int> disc;
int oper[MAX_SIZE][3];
int tmp[MAX_SIZE];
unordered_map<int, int> vis;
int q;

void takeseat(int id) {
    seat s = *st.begin();
    int len = s.r - s.l - 1;
    int pos = len / 2 + s.l + 1;
    seat s1 = seat{s.l, pos};
    seat s2 = seat{pos, s.r};
    st.erase(s);
    st.insert(s1), st.insert(s2);
    mp[pos] = s1;
    mp[s.r] = s2;
    vis[id] = pos;
}

void leave(int id) {
    int pos = vis[id];
    seat s1 = mp[pos];
    seat s2 = mp.upper_bound(pos)->second;
    seat s = seat{s1.l, s2.r};
    //cout << "create " << s1.l << " " << s2.r << endl;
    st.erase(s1), st.erase(s2);
    //cout << "eliminate " << s1.l << " " << s1.r << " , " << s2.l << " " << s2.r << endl;
    st.insert(s);
    mp.erase(pos);
    mp[s2.r] = s;
    vis[id] = -1;
}

int main() {
    int i;
    int cnt = 0;
    scanf("%d%d", &n, &q);
    seat ns = seat{0, n + 1};
	mp[n + 1] = ns; 
	st.insert(ns);
	for (i = 1; i <= q; i++) {
		int v;
		scanf("%d", &v);
		if (v > 0) {
		    if (vis.find(v) == vis.end() || vis[v] == -1) {
		        takeseat(v);
		        //cout << "take the seat " << vis[v] << endl;
		        tmp[cnt++] = vis[v];
		        oper[i][0] = 1, oper[i][1] = vis[v];
		    } else {
		        oper[i][0] = 2, oper[i][1] = vis[v];
		        leave(v);
		    }
		} else {
		   int l, r;
		   scanf("%d%d", &l, &r);
		   oper[i][0] = v, oper[i][1] = l, oper[i][2] = r;
		   tmp[cnt++] = l;
		   tmp[cnt++] = r;
		}
	}
	
	sort(tmp, tmp + cnt);
	
	for (i = 0 ; i < cnt; i++) {
	    if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	
	tree.setsize(disc.size());
	
	for (i = 1; i <= q; i++) {
	    if (oper[i][0] == 0) {
	        int L = lower_bound(disc.begin(), disc.end(), oper[i][1]) - disc.begin() + 1;
	        int R = lower_bound(disc.begin(), disc.end(), oper[i][2]) - disc.begin() + 1;
	        printf("%d\n", tree.query(L, R));
	    } else if (oper[i][0] == 1) {
	        int idx = lower_bound(disc.begin(), disc.end(), oper[i][1]) - disc.begin() + 1;
	        tree.update(idx, 1);
	    } else {
	        int idx = lower_bound(disc.begin(), disc.end(), oper[i][1]) - disc.begin() + 1;
	        tree.update(idx, -1);
	    }
	}
	return 0;
}
