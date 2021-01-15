#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

struct Index {
    int v1, v2, v3;
    bool operator < (Index other) const {
        return v1 < other.v1;
    }
};

int tree[MAX_SIZE];
int n;

int shift(int x) {
	return x & (-x);
}

void update(int pos, int v) {
	if (pos < 1) return;
	while (pos <= n) {
		tree[pos] += v;
		pos += shift(pos);
	}
}

int query(int pos) {
	int ret = 0;
	while (pos > 0) {
		ret += tree[pos];
		pos -= shift(pos);
	}
	return ret;
}

struct qrs {
	// x, y, v, id
	int x, y, v, id, si;
};

qrs vc[MAX_SIZE << 3];
int ans[MAX_SIZE];
qrs tmp[MAX_SIZE << 3];
int cnt = 0;
// we need to support 2 types of queries
// increment(x, y) by 1, increment(x, y) by -1
// and query(1, 1, x, y)
// good news is the timestamp has already be sorted
// in ascending order, we don't need to worry about that
void cdq(int l, int r) {
	if (l >= r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	vector<pair<int, int>> hist;
	int i = l, j = mid + 1, k = 0;
	while (i <= mid && j <= r) {
		if (vc[i].x <= vc[j].x) {
			update(vc[i].y, vc[i].v);
			hist.emplace_back(vc[i].y, -vc[i].v);
			tmp[k++] = vc[i++];
		} else {
			ans[vc[j].id] += vc[j].si * query(vc[j].y);
			tmp[k++] = vc[j++];
		}
	}
	
	while (i <= mid) {
		tmp[k++] = vc[i++];
	}
		
	while (j <= r) {
		ans[vc[j].id] += vc[j].si * query(vc[j].y);
		tmp[k++] = vc[j++];
	}
	
	for (i = l; i <= r; ++i) {
		vc[i] = tmp[i-l];
	}
	
	for (auto h : hist) {
		update(h.first, h.second);
	}
}

Index pos[MAX_SIZE];

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 0 ; i < 3; ++i) {
        for (j = 1; j <= n; ++j) {
            int v;
            scanf("%d", &v);
            if (i == 0) pos[v].v1 = j;
            if (i == 1) pos[v].v2 = j;
            if (i == 2) pos[v].v3 = j;
        }
    }

    sort(pos + 1, pos + 1 + n);
    int sz = 0;
    for (i = 1; i <= n; ++i) {
        vc[sz].x = pos[i].v2;
        vc[sz].y = pos[i].v3;
        vc[sz].si = 1;
        vc[sz].id = i;
        vc[sz++].v = 0;
        vc[sz].x = pos[i].v2;
        vc[sz].y = pos[i].v3;
        vc[sz].si = 0;
        vc[sz].id = 0;
        vc[sz++].v = 1;
    }

    cdq(0, sz - 1);
    long long ret = 0;
    for (i = 1; i <= n; ++i) {
        ret = ret + ans[i];
    }

    cout << ret << endl;
    return 0;
}