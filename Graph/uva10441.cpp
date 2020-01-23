#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXV 28
typedef long long ll;
using namespace std;

vector<pair<string, int>> g[MAXV];
int outdegree[MAXV], indegree[MAXV];
int f[MAXV];
bool visited[1011];
vector<string> ret;

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int a, int b) {
    int x = find(a), y = find(b);
    f[x] = y;
}

void init() {
	 int i;
	 memset(visited, false, sizeof(visited));
	 for (i = 0 ; i < MAXV; i++) {
	 	 g[i].clear();
	     f[i] = i, outdegree[i] = indegree[i] = 0;
	     ret.clear();
	 }	 
}

void dfs(int v) {
    int i;
    for (i = 0; i < g[v].size(); i++) {
        if (!visited[g[v][i].second]) {
            visited[g[v][i].second] = true;
            int nv = (g[v][i].first[g[v][i].first.size() - 1]) - 'a'; 
			dfs(nv);
            ret.push_back(g[v][i].first);
        }
    }
}

char st[22];

int main() {
	int T, n, i;
	#ifdef DEBUG
	freopen("out.txt", "w", stdout);
	#endif
	scanf("%d", &T);
	while (T > 0) {
	    scanf("%d", &n);
	    init();
	    set<char> h;
	    for (i = 0 ; i < n; i++) {
	        scanf("%s", st);
	        string s = string(st);
	        g[s[0] - 'a'].emplace_back(s, i);
	        outdegree[s[0] - 'a']++, indegree[s[s.size() - 1] - 'a']++;
	        h.insert(s[0]), h.insert(s[s.size() - 1]);
	        unionset(s[0] - 'a', s[s.size() - 1] - 'a');
	    }
	    
	    bool valid = true;
	    
	    int cng1 = 0, c1 = 0, sv = -1;
	    for (i = 0 ; i < MAXV; i++) {
	        if (outdegree[i] - indegree[i] == -1) {
	            cng1++;
	        } else if (outdegree[i] - indegree[i] == 1) {
	            c1++;
	            sv = i;
	        } else if (outdegree[i] != indegree[i]) {
	            valid = false;    
	        } 
	    }
	    
	    if (valid && ((c1 == 1 && cng1 == 1) || (c1 == 0 && cng1 == 0))) {
	        valid = true;
	    } else {
	        valid = false;
	    }
	    
	    unordered_set<int> prt;
	    for (auto ch : h) {
	        prt.insert(find(ch - 'a'));
	    }
	    
	    if (prt.size() > 1) valid = false;
	    if (sv == -1 && valid) {
	        sv = *h.begin() - 'a';
	    }
	    
	    
	    if (!valid) {
	        printf("***\n");
	    } else {
	        for (i = 0 ; i < MAXV; i++) sort(g[i].begin(), g[i].end());
	        dfs(sv);
	        reverse(ret.begin(), ret.end());
	        printf("%s", ret[0].c_str());
	        for (i = 1; i < ret.size(); i++) {
	            printf(".%s", ret[i].c_str());
	        }
	        printf("\n");
	    }
	    T--;
	}
	return 0;
}

