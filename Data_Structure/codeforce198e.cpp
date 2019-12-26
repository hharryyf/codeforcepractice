#include <bits/stdc++.h>
#define INF 1000000007ll
#define MAX_SIZE 524292

typedef long long ll;
using namespace std;

struct point {
	int p, wt;
	ll dist, r;
};

// collect[i] = 1 means the ith piece has been collected
int collected[MAX_SIZE >> 1]; 

point pt[MAX_SIZE >> 1];
map<ll, unordered_set<int>, greater<ll> > mp[MAX_SIZE]; 
// range min range tree
ll tree[MAX_SIZE];
/*
  1. use mi to do point compression and the axis of the range tree
  2. for each root node store a map<ll, unordered_set<int> > that represents the points in that chunk
  3. the points are sorted in decreasing order of dist^2 to the starting point, and the vector<int> represents
     the points id that belongs to this dist^2	 
*/
int tmp[MAX_SIZE >> 1];
vector<int> disc;
// all the active points
queue<point> q;

int n;

void build(int l, int r, int index) {
	 int mid = l + (r - l) / 2;
	 if (l > r) return;
	 if (l == r) {
	 	tree[index] = INF * INF;
	 	return;
	 }
	 
	 build(l, mid, index * 2);
	 build(mid + 1, r, index * 2 + 1);
	 tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}
// return the minimum (dist, id) pair that satisfy the condition r >= dist
pair<ll, int> query(int start, int end, int l, int r, int index, ll dist) {
     if (start > end || l > r || start > r || l > end) return make_pair(INF * INF, -1);
     if (tree[index] > dist) return make_pair(INF * INF, -1);
     int mid = l + (r - l) / 2;
	 if (start <= l && r <= end) {
	 	if (l == r) {
 		   auto pp = mp[l].lower_bound(dist);
		   return make_pair(pp->first, *pp->second.begin());
        }
        
        if (tree[index * 2 + 1] <= dist) {
		   return query(start, end, mid + 1, r, index * 2 + 1, dist);
		}
        return query(start, end, l, mid, index * 2, dist);
	 }
	 
	 return min(query(start, end, l, mid, index * 2, dist), 
	            query(start, end, mid + 1, r, index * 2 + 1, dist));
}

// tp = 0, remove, tp = 1, insert
void update(int pos, int l, int r, int index, ll dist, int id, int tp) {
	 if (pos < l || pos > r || l > r) return;
	 if (pos == l && l == r) {
	 	if (tp) {
		   mp[pos][dist].insert(id);
		   tree[index] = min(tree[index], mp[pos].rbegin()->first); 
	    } else {
    	   mp[pos][dist].erase(id);
    	   if (mp[pos][dist].size() == 0) {
		   	  mp[pos].erase(dist);
		   }
		   
		   if (mp[pos].size() == 0) {
		       tree[index] = INF * INF;
		   } else {
	 	   	   tree[index] = mp[pos].rbegin()->first; 
		   }
		}
	 	return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 if (pos <= mid) {
	 	update(pos, l, mid, index * 2, dist, id, tp);
	 } else {
	    update(pos, mid + 1, r, index * 2 + 1, dist, id, tp);
	 }
	 tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}

int getindex(int num) {
	return upper_bound(disc.begin(), disc.end(), num) - disc.begin() - 1;
}

int main() {
	int i;
	ll x, y, r;
	int p;
	scanf("%lld%lld%d%lld%d", &x, &y, &p, &r, &n);
	q.push(point{p, INF, 0, r * r});
	for (i = 1; i <= n; i++) {
		ll xi, yi, ri;
		int pi, mi;
		scanf("%lld%lld%d%d%lld", &xi, &yi, &mi, &pi, &ri);
		pt[i].dist = (xi - x) * (xi - x) + (yi - y) * (yi - y);
		pt[i].wt = mi;
		pt[i].p = pi;
		pt[i].r = ri * ri;
		tmp[i] = mi;
	}
	
	sort(tmp + 1, tmp + 1 + n);
	
	for (i = 1; i <= n; i++) {
		if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	
	int m = (int) disc.size();
	build(0, m - 1, 1);
	
	for (i = 1; i <= n; i++) {
		update(getindex(pt[i].wt), 0, m - 1, 1, pt[i].dist, i, 1);
	}
	
	while (!q.empty()) {
        point pp = q.front();
        q.pop();
        while (true) {
            auto pi = query(0, getindex(pp.p), 0, m - 1, 1, pp.r);
            if (pi.first == INF * INF || pi.second == -1) break;
            if (!collected[pi.second]) {
			   collected[pi.second] = 1;
			   q.push(pt[pi.second]);
			   update(getindex(pt[pi.second].wt), 0, m - 1, 1, pt[pi.second].dist, pi.second, 0);
			}
		}
	}	
	
	int cnt = 0;
	for (i = 1; i <= n; i++) {
		if (collected[i]) {
		   cnt++;
		}
	}
	
	printf("%d\n", cnt);
	return 0;
}
