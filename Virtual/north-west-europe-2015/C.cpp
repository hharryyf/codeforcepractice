#include <bits/stdc++.h>
#define MAX_SIZE 2111
using namespace std;
typedef long long ll;
struct pt2 {
    ll x, y;
    pt2() {}
    pt2(ll _x, ll _y) : x(_x), y(_y) {}
    pt2 operator-(const pt2& p) const { return pt2(x - p.x, y - p.y); }
    ll cross(const pt2& p) const { return x * p.y - y * p.x; }
    ll cross(const pt2& a, const pt2& b) const { return (a - *this).cross(b - *this); }
};

int sgn2(const ll & x) { return x >= 0 ? x ? 1 : 0 : -1; }

bool inter1(ll a, ll b, ll c, ll d) {
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}

bool check_inter(const pt2& a, const pt2& b, const pt2& c, const pt2& d) {
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
        return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);
    return sgn2(a.cross(b, c)) != sgn2(a.cross(b, d)) &&
           sgn2(c.cross(d, a)) != sgn2(c.cross(d, b));
}

struct segment {
	pt2 v1, v2;
};

int wid[MAX_SIZE];
pt2 pt[MAX_SIZE], wt[MAX_SIZE];
segment seg[MAX_SIZE];
vector<int> g[MAX_SIZE];
int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
stack<int> st;
int cnt = 0, cid = 1;

int neg(int x) {
    return x * 2;
}

int pos(int x) {
    return x * 2 - 1;
}

void tarjan(int v) {
    st.push(v);
    instack[v] = 1;
    visited[v] = low[v] = ++cnt;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            tarjan(nv);
            low[v] = min(low[v], low[nv]);
        } else if (instack[nv]) {
            low[v] = min(low[v], visited[nv]);
        }
    }

    if (low[v] == visited[v]) {
        while (st.top() != v) {
            instack[st.top()] = 0;
            cmpid[st.top()] = cid;
            st.pop();
        }

        cmpid[st.top()] = cid++;
        instack[st.top()] = 0;
        st.pop();

    }
}

int main() {
    int W, P, i, j;
    scanf("%d%d", &W, &P);
    for (i = 1; i <= W; ++i) {
        cin >> wt[i].x >> wt[i].y;
    }

    for (i = 1; i <= P; ++i) {
        cin >> wid[i] >> pt[i].x >> pt[i].y;
        seg[i].v1 = pt2(wt[wid[i]].x, wt[wid[i]].y);
        seg[i].v2 = pt[i];
    }

    for (i = 1; i <= P; ++i) {
        for (j = i + 1; j <= P; ++j) {
            if (wid[i] == wid[j]) continue;
            if (check_inter(seg[i].v1, seg[i].v2, seg[j].v1, seg[j].v2)) {
                g[pos(i)].push_back(neg(j));
                g[pos(j)].push_back(neg(i));
                g[neg(i)].push_back(pos(j));
                g[neg(j)].push_back(pos(i));
            }
        }
    }

    for (i = 1; i <= 2 * P; ++i) {
        if (!visited[i]) tarjan(i);
    }

    for (i = 1; i <= P; ++i) {
        if (cmpid[pos(i)] == cmpid[neg(i)]) {
            printf("impossible\n");
            return 0;
        }
    }

    printf("possible\n");
    return 0;
}