#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 524292
using namespace std;

struct BIT {
    int tree[MAX_SIZE];
    int N;

    void init(int N) {
        this->N = N;
    }

    int shift(int x) {
        return x & (-x);
    }
    
    int query(int idx) {
        int ret = 0;
        while (idx > 0) {
            ret += tree[idx], idx -= shift(idx);
        }
        return ret;
    }

    void update(int idx, int val) {
        if (idx <= 0) return;
        while (idx <= N) {
            tree[idx] += val, idx += shift(idx);
        }
    }
};

BIT tree;

struct event {
    // (x, y), the coordinate of the right-up point
    // event time, update value, update sign
    int x, y, ti, val, si;
};

vector<event> evt;
// set of disjointed segments
set<pair<int, int>> st;
int N, Q;
int ok[MAX_SIZE];
int ans[MAX_SIZE];
char s[11], light[MAX_SIZE];
int a[MAX_SIZE];
vector<pair<int, int>> history;

void divc(int l, int r) {
    if (l >= r) return;
    vector<event> tmp;
	vector<pair<int, int>> del;
	int mid = (l+r) >> 1;
	divc(l, mid);
	divc(mid + 1, r);
	int i = l, j = mid + 1;
	while (i <= mid && j <= r) {
		if (evt[i].x <= evt[j].x) {
			tree.update(evt[i].y, evt[i].val * evt[i].si);
			del.push_back(make_pair(evt[i].y, -evt[i].val * evt[i].si));
			tmp.push_back(evt[i]);
			i++;
		} else {
			ans[evt[j].ti] += tree.query(evt[j].y) * evt[j].si;
			tmp.push_back(evt[j]);
			j++;
		}
	}
	while (i <= mid) {
		tmp.push_back(evt[i++]);
	}
	
	while (j <= r) {
		ans[evt[j].ti] += tree.query(evt[j].y) * evt[j].si;
		tmp.push_back(evt[j]);
		j++;
	}
	
	for (i = l; i <= r; ++i) {
		evt[i] = tmp[i-l];
	}
	
	for (i = 0 ; i < (int) del.size(); ++i) {
		tree.update(del[i].first, del[i].second);
	}
}

void addevent(int x, int y, int ti, int val, int si) {
    if (x <= 0 || y <= 0) return;
    evt.push_back(event{x, y, ti, val, si});
}

int main() {
    int i, l = -1, r = -1;
    scanf("%d%d", &N, &Q);
    scanf("%s", light+1);
    tree.init(N + 4);
    // initialize the lights
    for (i = 1; i <= N; ++i) {
        a[i] = light[i] - '0';
        if (light[i] == '1') {
            if (l == -1) {
                l = i, r = i;
            } else {
                ++r;
            }
        } else {
            if (l != -1) {
                st.insert(make_pair(l, r));
                // update the square [l, l, r, r] += Q at time 0
                addevent(r + 1, r + 1, 0, Q, 1);
                addevent(l, r + 1, 0, Q, -1);
                addevent(r + 1, l, 0, Q, -1);
                addevent(l, l, 0, Q, 1);
            }
            l = -1, r = -1;
        } 
    }

    if (l != -1 && r != -1) {
        st.insert(make_pair(l, r));
        addevent(r + 1, r + 1, 0, Q, 1);
        addevent(l, r + 1, 0, Q, -1);
        addevent(r + 1, l, 0, Q, -1);
        addevent(l, l, 0, Q, 1);
    }


    for (i = 1; i <= Q; ++i) {
        scanf("%s", s);
        if (s[0] == 't') {
            scanf("%d", &l);
            if (a[l] == 0) {
                st.insert(make_pair(l, l));
                auto p = st.lower_bound(make_pair(l, l));
                if (p != st.begin()) {
                    p = prev(p);
                    if (p->second == l-1) {
                        int L = p->first;
                        st.erase(p);
                        st.erase(make_pair(l, l));
                        st.insert(make_pair(L, l));
                    }
                }

                p = st.upper_bound(make_pair(l, l));
                if (p != st.end() && p->first == l + 1) {
                    int L = -1, R = p->second;
                    auto p1 = prev(p);
                    L = p1->first;
                    st.erase(*p1);
                    st.erase(*p);
                    st.insert(make_pair(L, R));
                }

                p = prev(st.upper_bound(make_pair(l, N + 4)));
                addevent(l + 1, p->second + 1, i, Q - i, 1);
                addevent(p->first, p->second + 1, i, Q - i, -1);
                addevent(l + 1, l, i, Q - i, -1);
                addevent(p->first, l, i, Q - i, 1);
            } else {
                auto p = st.upper_bound(make_pair(l, N + 1));
                p = prev(p);
                auto p1 = make_pair(p->first, l - 1);
                auto p2 = make_pair(l + 1, p->second);
                // we eliminate the range [p->first, l, l, p->second]
                addevent(l + 1, p->second + 1, i, Q - i, -1);
                addevent(p->first, p->second + 1, i, Q - i, 1);
                addevent(l + 1, l, i, Q - i, 1);
                addevent(p->first, l, i, Q - i, -1);
                st.erase(*p);
                st.insert(p1);
                st.insert(p2);
            }

            a[l] ^= 1;
        } else {
            scanf("%d%d", &l, &r);
            r--;
            // check the value of point [l,r]
            addevent(l, r, i, 0, 1);
            ok[i] = 1;
            if (!st.empty()) {
                auto p = st.upper_bound(make_pair(l, N + 4));
                if (p != st.begin()) {
                    p = prev(p);
                    if (p->first <= l && p->second >= r) {
                        ans[i] -= Q - i;
                    }
                }
            }
        }
    }

    divc(0, (int) evt.size() - 1);

    for (i = 1; i <= Q; ++i) {
        if (ok[i]) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}