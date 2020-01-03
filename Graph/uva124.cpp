#include <bits/stdc++.h>
#define MAX_SIZE 29
using namespace std;

vector<int> g[MAX_SIZE];
char st[211];
char cst[211];
set<char> chs;
int ans[MAX_SIZE];
int indegree[MAX_SIZE];
void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; i++) {
        g[i].clear();
        indegree[i] = 0;
    }
    chs.clear();
}

/* 
    extract all top-sort order using the Kahn's algorithm and backtracking
*/

void topsort(int depth) {
    int i;
    if (depth == chs.size()) {
        for (i = 0 ; i < depth; i++) {
            printf("%c", ans[i] + 'a');
        }
        printf("\n");
        return;
    }
    
    for (auto c : chs) {
        int v = c - 'a';
        if (indegree[v] == 0) {
            indegree[v]--;
            ans[depth] = v;
            for (auto nv : g[v]) {
                indegree[nv]--;
            }
            topsort(depth + 1);
            for (auto nv : g[v]) {
                indegree[nv]++;
            }
            indegree[v]++;
        }
    }
}

int main() {
    int i;
    int cnt = 1;
    while (fgets(st, 211, stdin) != NULL) {
        fgets(cst, 211, stdin);
        init();
        if (cnt > 1) {
            cout << endl;
        }
        string str = st;
		istringstream ss(str);
		while (ss >> str) {
			chs.insert(str[0]);
		}
		
		vector<char> tmp;
		str = cst;
		istringstream s2(str);
		while (s2 >> str) {
		    tmp.push_back(str[0]);
		}
		
		int i;
		for (i = 0 ; i < tmp.size(); i += 2) {
		    g[tmp[i] - 'a'].push_back(tmp[i+1] - 'a');
		}
		
		for (i = 0 ; i < MAX_SIZE; i++) {
		    for (auto v : g[i]) {
		        indegree[v]++;
		    }    
		}
		
#ifdef DEBUG
		cout << "all the letters " << endl;
		for (auto ch : chs) {
		    cout << ch << " ";
		}
		cout << endl;
		cout << "all the constraints " << endl;
		for (i = 0 ; i < MAX_SIZE; i++) {
		    if (!g[i].empty()) {
		        printf("%c < ", i + 'a');
		        for (auto c : g[i]) {
		            printf(" %c ", c + 'a');
		        }
		        cout << endl;
		    }
		}
		cout << endl;
#endif
        cnt++;
        topsort(0);
    }
    return 0;
}
