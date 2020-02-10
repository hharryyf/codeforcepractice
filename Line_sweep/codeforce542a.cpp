#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

struct segt {
	   int rval;
	   int rmax;
};

segt tree1[MAX_SIZE], tree2[MAX_SIZE];
ll ans = 0;
int id = 0;
// all distinct l in ascending order
vector<int> disc1;
// all distinct r in ascending order
vector<int> disc2;

segt pullup(segt t1, segt t2, int tp) {
	 segt t;
	 if (tp == 1) {
	 	t.rval = max(t1.rval, t2.rval);
	 } else {
	    t.rval = min(t1.rval, t2.rval);
	 }
	 t.rmax = max(t1.rmax, t2.rmax);
	 return t;
}

// update pos rval = max(r, val) and rmax = rval- disc[pos]
void update(int pos, int l, int r, int index, int val, int tp) {
	 if (pos < l || pos > r || l > r) return;
	 if (l == r && l == pos) {
	 	if (tp == 1) {
	 		tree1[index].rval = max(tree1[index].rval, val);
	 		tree1[index].rmax = max(tree1[index].rval - disc1[pos], 0);
		} else {
		    tree2[index].rval = min(tree2[index].rval, val);
			tree2[index].rmax = max(disc2[pos] - tree2[index].rval, 0);    
		}
	 	return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 if (pos <= mid) {
	 	update(pos, l, mid, index * 2, val, tp);
	 } else {
	    update(pos, mid + 1, r, index * 2 + 1, val, tp);
	 }
	 
	 if (tp == 1) {
	 	tree1[index] = pullup(tree1[index * 2], tree1[index * 2 + 1], 1);
	 } else {
	    tree2[index] = pullup(tree2[index * 2], tree2[index * 2 + 1], 0);
	 }
}
// query, return a struct
segt query(int start, int end, int l, int r, int index, int tp) {
	 if (start > end || l > r) {
	 	if (tp == 1) return segt{0,0};
	 	return segt{MOD, 0};
	 }
	 if (start <= l && r <= end) {
		 if (tp == 1) {
		 	return tree1[index];		 
		 } 
		 return tree2[index];
	 }
	 
	 int mid = l + (r - l) / 2;
	 if (end <= mid) return query(start, end, l, mid, index * 2, tp);
	 if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1, tp);
	 return pullup(query(start, end, l, mid, index * 2, tp), query(start, end, mid + 1, r, index * 2 + 1, tp), tp);
}


struct qrs {
	   int l, r, id;
	   bool operator < (qrs other) const {
	   		if (l != other.l) return l < other.l;
	   		return id < other.id;
	   }
};

bool useless[MAX_SIZE << 1];
int cost[MAX_SIZE << 1];
qrs org[MAX_SIZE << 1];
qrs video[MAX_SIZE << 1];
qrs channel[MAX_SIZE << 1];
int tmp1[MAX_SIZE << 1], tmp2[MAX_SIZE << 1];
int n, m;

static bool cmp(const qrs &q1, const qrs &q2) {
	   return q1.r < q2.r;
}
// check whether a channel is fully covered by a video, if so mark the channel id
// and update the answer
void solve_1() {
	 int i, j;
	 for (i = 0 ; i < MAX_SIZE; i++) tree2[i].rval = MOD;
	 set<qrs> s;
	 sort(video + 1, video + 1 + n, cmp);
	 sort(channel + 1, channel + 1 + m, cmp);
	 for (i = 1, j = 1; i <= n; i++) {
	 	 while (j <= m && video[i].r >= channel[j].r) {
		 	   s.insert(channel[j]); 
		       j++;	   
         }
         
         auto iter = s.lower_bound(qrs{video[i].l, 0, 0});
         while (iter != s.end()) {
		 	   auto it = iter;
		 	   useless[it->id] = true;
       		   if (1ll * cost[it->id] * (it->r - it->l) > ans) {
				  ans = 1ll * cost[it->id] * (it->r - it->l);
				  id = it->id;
		       }
		 	   iter++;
		 	   s.erase(it);
		 }
	 }
}

// sort the channel and video according to the right endpoint
// i iterate over the channels, j iterate over the videos
void solve_2() {
	 int i, j;
	 for (i = 1, j = 1; i <= m; i++) {
	 	 if (useless[channel[i].id]) continue;
	 	 while (j <= n && channel[i].r >= video[j].r) {
		 	 int index = lower_bound(disc1.begin(), disc1.end(), video[j].l) - disc1.begin();  
		     update(index, 0, (int) disc1.size() - 1, 1, video[j].r,1);
			 j++; 
         }
         
         int idx = lower_bound(disc1.begin(), disc1.end(), channel[i].l) - disc1.begin();
		 segt ret1 = query(0, idx - 1, 0, (int) disc1.size() - 1, 1, 1);
		 segt ret2 = query(idx, (int) disc1.size() - 1, 0, (int) disc1.size() - 1, 1, 1);
		 int len = max(ret1.rval - channel[i].l, ret2.rmax);
		 if (1ll * len * cost[channel[i].id] > ans) {
		 	ans = 1ll * len * cost[channel[i].id];
		 	id = channel[i].id;
		 } 
	 }
}

void solve_3() {
	 int i, j;
	 sort(video + 1, video + 1 + n);
	 sort(channel + 1, channel + 1 + m);
	 for (i = m, j = n; i >= 1; i--) {
	 	 if (useless[channel[i].id]) continue;
	 	 while (j >= 1 && channel[i].l <= video[j].l) {
		 	   int index = lower_bound(disc2.begin(), disc2.end(), video[j].r) - disc2.begin();
			   update(index, 0, (int) disc2.size() - 1, 1, video[j].l, 0);
			   j--; 
         }
         
         int idx = lower_bound(disc2.begin(), disc2.end(), channel[i].r) - disc2.begin();
         segt ret1 = query(idx, (int) disc2.size() - 1, 0, (int) disc2.size() - 1, 1, 0);
         segt ret2 = query(0, idx - 1, 0, (int) disc2.size() - 1, 1, 0);
         int len = max(channel[i].r - ret1.rval, ret2.rmax);
         if (1ll * len * cost[channel[i].id] > ans) {
		 	ans = 1ll * len * cost[channel[i].id];
		 	id = channel[i].id;
		 }
	 }
}

int intersect(qrs q1, qrs q2) {
	return max(0, min(q1.r, q2.r) - max(q1.l, q2.l));
}


int main() {
	int i;
	scanf("%d%d", &n, &m);
	for (i = 1 ; i <= n; i++) {
		scanf("%d%d", &video[i].l, &video[i].r);
		video[i].id = i;
		tmp1[i] = video[i].l, tmp2[i] = video[i].r;
	}
	
	sort(tmp1 + 1, tmp1 + 1 + n);
	sort(tmp2 + 1, tmp2 + 1 + n);
	for (i = 1; i <= n; i++) {
		if (i == 1 || tmp1[i] != tmp1[i-1]) disc1.push_back(tmp1[i]);
		if (i == 1 || tmp2[i] != tmp2[i-1]) disc2.push_back(tmp2[i]); 
	}
	
	for (i = 1; i <= m; i++) {
		scanf("%d%d%d", &channel[i].l, &channel[i].r, &cost[i]);
		channel[i].id = i;
		org[i] = channel[i];
	}
	
	
	solve_1();
	//cout << ans << endl;
	solve_2();
	//cout << ans << endl;
	solve_3();
	//cout << ans << endl;
	if (ans > 0) {
        printf("%lld\n", ans);
        for (i = 1; i <= n; i++) {
			if (1ll * intersect(video[i], org[id]) * cost[id] == ans) {
			   printf("%d %d\n", video[i].id, id);
			   break;
			}
		}
	} else {
	    printf("%lld\n", ans);
	}
	return 0;
}

