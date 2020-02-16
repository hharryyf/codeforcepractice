#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 300111
typedef long long ll;
using namespace std;

// first observation, there's no multi cycle in the graph
// the reson is suppose that there's a multi-cycle the graph then consider the
// common edges shared by 2 cycles, if it has odd number of edges, then the outmost
// cycle must be an even cycle, contradiction! if it has even number of edges, then
// the out most cycle must be an even cycle, contradiction!
// second observation, based on the first observation, if we do tarjan's biconnected 
// component algorithm on this undirected graph, we would get a forest
// so [l, r] simply asks how many [x, y] which l <= x, y <= r such that
// no biconnected component with size greater than 1 has it vertices completely 
// within [x, y]

// this problem can be efficiently solved by using a line sweeping technique
// we establish a range tree, which each node represents use the current node
// as x, how far can it extend to the right
// also, we establish a counting data structure, which maintain how many nodes 
// have been set a right bound 

class BIT {
public:
	   ll t[MAX_SIZE];
	   int n;
	   
	   void setsize(int n) {
	   		this->n = n;
	   }
	   
	   int shift(int x) {
	   	   return x & (-x);
	   }
	   
	   void update(int index, ll val) {
	   		while (index <= n) {
   	  		    t[index] += val;
   	  			index += shift(index);
			}		
	   }
	   
	   ll getans(int index) {
	   	    ll ret = 0;
		    while (index > 0) {
			     ret += t[index];
			     index -= shift(index);
		    }
		    return ret;
	   }
	   
	   
	   ll query(int l, int r) {
	   	   return getans(r) - getans(l-1);
	   }
	   
	   void setval(int index, ll val) {
	        ll v1 = query(index, index);
	        update(index, -v1);
	        update(index, val);
	   }
};

stack<int> st;
list<int> s;
BIT t1, t2;
int k = 1;
int visited[MAX_SIZE];
int instack[MAX_SIZE];
int low[MAX_SIZE];
int cmpid[MAX_SIZE];
vector<int> g[MAX_SIZE];
ll ans[MAX_SIZE];
// left[i] represents the min affected node of component i
// right[i] represents the max affected node of component i
int lft[MAX_SIZE], rt[MAX_SIZE];
struct qrs {
    int l, r;
    int id;
    bool operator < (qrs other) const {
        return r < other.r;
    }
};

vector<qrs> itv;
qrs q[MAX_SIZE];

void tarjan(int v, int pre) {
	visited[v] = low[v] = k++;
	instack[v] = true;
	st.push(v);
	for (auto nv : g[v]) {
	    if (nv != pre) {
	        if (!visited[nv]) {
	            tarjan(nv, v);
	            low[v] = min(low[v], low[nv]);
	        } else if (instack[nv]) {
	            low[v] = min(low[v], visited[nv]);
	        }
	    }
	}
	
	if (low[v] == visited[v]) {
	    while (st.top() != v) {
	        cmpid[st.top()] = v;
	        instack[st.top()] = false;
	        st.pop();
	    }
	    cmpid[st.top()] = v;
	    instack[st.top()] = false;
	    st.pop();
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	t1.setsize(n), t2.setsize(n);
	int i, j;
	for (i = 1; i <= n; i++) {
	    t1.update(i, 1);
	    t2.update(i, n);
	    s.push_back(i);
	}
	
	for (i = 1; i <= m; i++) {
	    int v1, v2;
	    scanf("%d%d", &v1, &v2);
	    g[v1].push_back(v2), g[v2].push_back(v1);
	}
	
	for (i = 1; i <= n; i++) {
	    if (!visited[i]) tarjan(i, 0);
	    lft[i] = n+1, rt[i] = 0;
	}
	
	for (i = 1; i <= n; i++) {
	    lft[cmpid[i]] = min(i, lft[cmpid[i]]);
	    rt[cmpid[i]] = max(i, rt[cmpid[i]]);
	}
	
	for (i = 1; i <= n; i++) {
	    if (lft[i] < rt[i]) {
	        itv.push_back(qrs{lft[i], rt[i], 0});
	    }
	}
	
	sort(itv.begin(), itv.end());
	
	scanf("%d", &m);
	for (i = 0; i < m; i++) {
	    scanf("%d%d", &q[i].l, &q[i].r);
	    q[i].id = i + 1;
	}
	
	sort(q, q + m);
	
	for (i = 0, j = 0 ; i < m; i++) {
	    while (j < itv.size() && q[i].r >= itv[j].r) {
	        while(!s.empty() && s.front() <= itv[j].l) {
	            t1.setval(s.front(), 0);
	            t2.setval(s.front(), itv[j].r-1);
	            s.pop_front();
	        }
	        j++;
	    }
	    
	    // cout << t2.query(q[i].l, q[i].r) << " " << t1.query(q[i].l, q[i].r) << endl;
	    ans[q[i].id] = t2.query(q[i].l, q[i].r) - t1.query(q[i].l, q[i].r) * (n-q[i].r) - 1ll * (q[i].l + q[i].r) * (q[i].r - q[i].l + 1) / 2 + 1ll * (q[i].r - q[i].l + 1);
	}
	
	for (i = 1; i <= m; i++) {
	    printf("%lld\n", ans[i]);
	}
	
	return 0;
}
