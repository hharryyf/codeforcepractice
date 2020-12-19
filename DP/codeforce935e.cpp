#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 15012
typedef long long ll;
using namespace std;
const ll inf = 100000000000ll;
int P, M;
int sz[MAX_SIZE];
ll dp[MAX_SIZE][111][2];
char pp[MAX_SIZE], ss[MAX_SIZE];
vector<int> g[MAX_SIZE];
int cnt = 0;

struct node {
    node *left, *right;
    char conn;
    int id;
    node(char conn, node* left, node* right) {
        this->conn = conn;
        this->left = left;
        this->right = right;
    }
};

node *root;

struct expression {

    node *build(char s[]) {
        return buildfromPrefix(convertToprefix(s));
    }

    int getpriority(char ep) {
        if (ep == '*' || ep == '/') return 2;
        if (ep == '+' || ep == '-') return 1;
        if (ep == '?') return 0;
        return -1;
    }

    node *buildfromPrefix(vector<char> s) {
        int len = s.size(), i;
        stack<node*> st;
        for (i = 0; i < len; ++i) {
            if (getpriority(s[i]) == -1) {
                st.push(new node(s[i], NULL, NULL));
            } else {
                if (getpriority(s[i]) == 2) {
                    node *nd = new node(s[i], NULL, st.top());
                    st.pop();
                    st.push(nd);
                } else {
                    node *f1 = st.top();
                    st.pop();
                    node *f2 = st.top();
                    st.pop();
                    node *f = new node(s[i], f2, f1);
                    st.push(f);
                }
            }
        }

        return st.top();
    }

    vector<char> convertToprefix(char s[]) {
        vector<char> ret;
        int i, len = strlen(s);
        stack<char> st;
        for (i = 0 ; i < len; ++i) {
            if (getpriority(s[i]) == -1) {
                if (s[i] == '(') {
                    st.push(s[i]);
                } else if (s[i] == ')') {
                    while (!st.empty() && st.top() != '(') {
                        ret.push_back(st.top());
                        st.pop();
                    }
                    st.pop();
                } else {
                    ret.push_back(s[i]);
                }
            } else {
                while (!st.empty() && (getpriority(s[i]) <= getpriority(st.top()))) {
                    ret.push_back(st.top());
                    st.pop();
                }
                st.push(s[i]);
            }
        }

        while (!st.empty()) {
            ret.push_back(st.top());
            st.pop();
        }
        return ret;
    }
};

expression ep;

void debug(node *rt, int dep=0) {
    if (rt == NULL) return;
    debug(rt->right, dep + 1);
    int i;
    for (i = 0 ; i < dep; ++i) printf("\t\t");
    printf("%c\n", rt->conn);
    debug(rt->left, dep + 1);
}

void order(node *rt) {
    if (rt == NULL) return;
    rt->id = ++cnt;
    ss[rt->id] = rt->conn;
    if (rt->conn == '?') sz[rt->id] = 1;
    order(rt->left);
    order(rt->right);
    if (rt->left != NULL) {
        sz[rt->id] += sz[rt->left->id];
        g[rt->id].push_back(rt->left->id);
    }

    if (rt->right != NULL) {
        sz[rt->id] += sz[rt->right->id];
        g[rt->id].push_back(rt->right->id);
    }
}

void dfs(int v) {
    if (ss[v] != '?') {
        dp[v][0][0] = dp[v][0][1] = ss[v] - '0';
        return;
    }

    int i, j, l = g[v][0], r = g[v][1];
    dfs(l);
    dfs(r);
    if (min(P, M) == P) {
        for (i = 0; i <= P; ++i) {
            for (j = 0 ; j <= i; ++j) {
                if (i - j - 1 >= 0 && i >= 1 && sz[v] - i >= 0 && sz[v] - i <= M) {
                    dp[v][i][0] = max(dp[l][j][0] + dp[r][i - j - 1][0], dp[v][i][0]);
                    dp[v][i][1] = min(dp[l][j][1] + dp[r][i - j - 1][1], dp[v][i][1]);
                }

                if (i - j >= 0 && sz[v] - i >= 0 && sz[v] - i <= M) {
                    dp[v][i][0] = max(dp[l][j][0] - dp[r][i - j][1], dp[v][i][0]);
                    dp[v][i][1] = min(dp[l][j][1] - dp[r][i - j][0], dp[v][i][1]);
                }
            }
        }
    } else {
        for (i = 0; i <= M; ++i) {
            for (j = 0 ; j <= i; ++j) {
                if (i - j - 1 >= 0 && i >= 1 && sz[v] - i >= 0 && sz[v] - i <= P) {
                    dp[v][i][0] = max(dp[l][j][0] - dp[r][i - j - 1][1], dp[v][i][0]);
                    dp[v][i][1] = min(dp[l][j][1] - dp[r][i - j - 1][0], dp[v][i][1]);
                }

                if (i - j >= 0 && sz[v] - i >= 0 && sz[v] - i <= P) {
                    dp[v][i][0] = max(dp[l][j][0] + dp[r][i - j][0], dp[v][i][0]);
                    dp[v][i][1] = min(dp[l][j][1] + dp[r][i - j][1], dp[v][i][1]);
                }
            }
        }
    }
}

int main() {
    int i, j;
    scanf("%s", pp);
    scanf("%d%d", &P, &M);
    for (i = 0 ; i < MAX_SIZE; ++i) {
        for (j = 0 ; j < 111; ++j) {
            dp[i][j][0] = -inf;
            dp[i][j][1] = inf;
        }
    }

    root = ep.build(pp);
    order(root);
    dfs(1);

    printf("%I64d\n", dp[1][min(P, M)][0]);
    return 0;
}