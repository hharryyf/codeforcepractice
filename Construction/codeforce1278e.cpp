#include <bits/stdc++.h>
#define MAX_SIZE 500011
using namespace std;

struct node {
    node *nxt;
    node *pre;
    int val;
    node(int val) {
        this->nxt = this->pre = NULL;
        this->val = val;
    }
};

vector<int> g[MAX_SIZE];
node *nd[MAX_SIZE][2];
int L[MAX_SIZE], R[MAX_SIZE];

void dfs(int v, int pre) {
    for (auto nv : g[v]) {
        if (nv != pre) {
            nd[nv][0] = new node(nv);
            nd[nv][1] = new node(nv);
            nd[nv][0]->nxt = nd[v][0];
            nd[nv][0]->pre = nd[v][0]->pre;
            nd[v][0]->pre->nxt = nd[nv][0];
            nd[v][0]->pre = nd[nv][0];
            nd[nv][1]->pre = nd[v][0];
            nd[nv][1]->nxt = nd[v][0]->nxt;
            nd[v][0]->nxt->pre = nd[nv][1];
            nd[v][0]->nxt = nd[nv][1];          
            dfs(nv, v);
        }
    }
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    nd[1][0] = new node(1);
    nd[1][1] = new node(1);
    nd[1][0]->nxt = nd[1][1];
    nd[1][1]->pre = nd[1][0];
    nd[0][0] = new node(1e8);
    nd[0][1] = new node(1e8);
    nd[0][0]->nxt = nd[1][0];
    nd[1][0]->pre = nd[0][0];
    nd[0][1]->pre = nd[1][1];
    nd[1][1]->nxt = nd[0][1];
    dfs(1, 0);
    auto curr = nd[0][0];
    i = 1;
    while (curr != NULL) {
        if (curr->val <= n) {
            if (!L[curr->val]) {
                L[curr->val] = i;
            } else {
                R[curr->val] = i;
            }

            i++;
        } 
        curr = curr->nxt;
    }

    for (i = 1; i <= n; ++i) {
        printf("%d %d\n", L[i], R[i]);
    }
    return 0;
}