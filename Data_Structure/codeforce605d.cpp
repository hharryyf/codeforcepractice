#include <bits/stdc++.h>
#define INF 1110000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;
/*
    This problem is doable and can be solved by myself within 1 hour.
	Firstly, it is quite obvious that we don't need to visit repeated states
    the problem simply reduce to a BFS problem.
    suppose that each point has (a, b, c, d), then (a, b) are the coordinate
    (c, d) are the query points, for each state transition, we simply find all
    nodes that haven't been visited and satisfy the condition that (a',b') < (c',d')
    then add those points to the queue and remove those points
    
    This would be another variant of problem 19D/198E, if range tree and sets are used together,
    the problem can be solved in O(nlogn) time.
*/

struct state {
	// a, b are the points, c, d are the queries
 	int a, b, c, d;
 	int id;
};

int tree[MAX_SIZE];
int visited[MAX_SIZE];
map<int, unordered_set<int>, greater<int> > mp[MAX_SIZE];
vector<int> disc;
queue<pair<state, int> > q;
state st[MAX_SIZE];
int tmp[MAX_SIZE];
int n;
int pre[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    tree[index] = INF;
    if (l == r) return;
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
    tree[index] = INF;
}

void update(int pos, int l, int r, int index, int val, int id, int tp) {
    if (l > r || pos < l || pos > r) return;
    if (l == r && r == pos) {
        if (tp) {
            mp[l][val].insert(id);
            tree[index] = mp[l].rbegin()->first;
        } else {
            mp[l][val].erase(id);
            if (mp[l][val].empty()) {
                mp[l].erase(val);
            }
            if (mp[l].empty()) {
                tree[index] = INF;
            } else {
                tree[index] = mp[l].rbegin()->first;
            }
        }
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (pos <= mid) {
        update(pos, l, mid, index * 2, val, id, tp);
    } else {
        update(pos, mid + 1, r, index * 2 + 1, val, id, tp);
    }
    
    tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}

// get leftmost the (b, id) pair
pair<int, int> query(int start, int end, int l, int r, int index, int mx) {
    if (start > end || l > r || start > r || l > end) return make_pair(INF, -1);
    if (tree[index] > mx) return make_pair(INF, -1);
    int mid = l + (r - l) / 2;
    if (start <= l && r <= end) {
        if (l == r) {
            auto pp = mp[l].lower_bound(mx);
            return make_pair(pp->first, *pp->second.begin());
        }
        if (tree[index * 2 + 1] <= mx) {
            return query(start, end, mid + 1, r, index * 2 + 1, mx);
        }
        return query(start, end, l, mid, index * 2, mx);
    }
    
    return min(query(start, end, l, mid, index * 2, mx), 
               query(start, end, mid + 1, r, index * 2 + 1, mx));
}

int getindex(int num) {
    return upper_bound(disc.begin(), disc.end(), num) - disc.begin() - 1;
}

int main() {
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
	    int a, b, c, d;
	    scanf("%d%d%d%d", &a, &b, &c, &d);
	    st[i] = state{a, b, c, d, i};
	    tmp[i] = a;
	}
	
	sort(tmp + 1, tmp + 1 + n);
	
	for (i = 1; i <= n; i++) {
	    if (i == 1 || tmp[i] != tmp[i-1]) {
	        disc.push_back(tmp[i]);
	    }
	}
	
	int m = disc.size();
	build(0, m - 1, 1);
	for (i = 1; i <= n; i++) {
	    update(getindex(st[i].a), 0, m - 1, 1, st[i].b, st[i].id, 1);
	}
	
	q.push(make_pair(state{0,0,0,0,0}, 0));
	int ans = -1;
	while (!q.empty()) {
	    auto pp = q.front();
	    q.pop();
	    state ss = pp.first;
	    int step = pp.second;
	    if (ss.id == n) {
	        ans = pp.second;
	        break;
	    }
	    
	    while (true) {
	        auto nxt = query(0, getindex(ss.c), 0, m - 1, 1, ss.d);
	        if (nxt.first == INF || nxt.second == -1) break;
	        if (!visited[nxt.second]) {
	            visited[nxt.second] = 1;
	            q.push(make_pair(st[nxt.second], step + 1));
	            update(getindex(st[nxt.second].a), 0, m - 1, 1, nxt.first, nxt.second, 0);
	            pre[nxt.second] = ss.id;
	        }
	    }
	}
	if (ans == -1) {
	    printf("-1\n");
	} else {
	    printf("%d\n", ans);
	    stack<int> stk;
	    i = n;
	    while (i > 0) {
	        stk.push(i);
	        i = pre[i];
	    }
	    
	    while (!stk.empty()) {
	        printf("%d ", stk.top());
	        stk.pop();
	    }
	}
	return 0;
}

