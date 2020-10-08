#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 300011

vector<int> g[MAX_SIZE];
char ss[MAX_SIZE];
int c[MAX_SIZE];
int cnt = 0, mx = 0;
struct node {
    int tol, end;
    map<char, node*> child;
    node() {
        this->tol = 0, this->end = 0;
    }
};

// merge t2 to t1
void merge(node *&t1, node *t2) {
    if (t2 == NULL) return;
    if (t1 == NULL) {
        t1 = t2;
        return;
    }

    for (auto ch : t2->child) {
        if (t1->child.count(ch.first)) {
            if (t1->child[ch.first]->end == 0 && ch.second->end == 1) {
                t1->child[ch.first]->end = 1;
                t1->child[ch.first]->tol++;
            }
            merge(t1->child[ch.first], ch.second);
        } else {
            t1->child[ch.first] = ch.second;
        }
    }

    t1->tol = t1->end;
    for (auto ch : t1->child) {
        t1->tol += ch.second->tol;
    }
}

node *dfs(int v, int pre) {
    node *ret = new node();
    for (auto nv : g[v]) {
        if (nv != pre) {
            node *nd = dfs(nv, v);
            if (ret->tol < nd->tol) {
                swap(ret, nd);
            }
            merge(ret, nd);
            // cout << "merge " << nv << " distinct= " << ret->tol << endl;
        }
    }

    node *nd = new node();
    nd->child[ss[v]] = ret;
    // cout << ret->tol << endl;
    nd->child[ss[v]]->end = 1;
    nd->child[ss[v]]->tol++;
    nd->tol = nd->child[ss[v]]->tol;
    if (nd->tol + c[v] > mx) {
        mx = nd->tol + c[v];
        cnt = 1;
    } else if (nd->tol + c[v] == mx) {
        cnt++;
    }

    // cout << v << " distinct = " << nd->tol << endl;
    return nd;
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%d", &c[i]);
    scanf("%s", ss + 1);
    for (i = 1; i < n; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    dfs(1, 0);
    printf("%d\n%d\n", mx, cnt);
    return 0;
}