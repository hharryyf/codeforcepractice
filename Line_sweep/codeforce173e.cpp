#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

int n, k, q;

struct people {
	int rep;
	int age;
	int id;
};

struct qrs {
	int l, r, id, y;
};

qrs qr[MAX_SIZE >> 1];

people a[MAX_SIZE >> 1], b[MAX_SIZE >> 1];

/*
	We consider this problem as two parts, first we need to work out how many
	people each one dominates, here dominates refers to this person as the
	group leader, how many people in his group
	
	sort every one according to the y coordinate non-decreasing order
	then line sweep and use a fenwick tree to store the answer
	
	Second step sort the queries according to decresing y order, line sweep and
	rmq to answer the queries
*/

// cont[i] stores how many people[i] controls if he is the group leader
int cont[MAX_SIZE];

// discrete the data according to age (x)
vector<int> disc;

int tmp[MAX_SIZE >> 1];

int tree[MAX_SIZE >> 1], rmq[MAX_SIZE];

int ans[MAX_SIZE >> 1];

static bool cp_1(const people &p1, const people &p2) {
	if (p1.rep != p2.rep) return p1.rep < p2.rep;
	return p1.age < p2.age;
}

static bool cp_2(const qrs &q1, const qrs &q2) {
	return q1.y > q2.y;
}

// return the smallest index >= num, + 1
int getlow(int num) {
	return lower_bound(disc.begin(), disc.end(), num) - disc.begin() + 1;
}

// return the maximum index <= num, + 1
int gethigh(int num) {
	return upper_bound(disc.begin(), disc.end(), num) - disc.begin();
}

int shift(int x) {
	return (x & (-x));
}

void add1(int index) {
	while (index <= n) {
		tree[index] += 1;
		index = index + shift(index);
	}
}

int getsum(int index) {
	int ret = 0;
	while (index > 0) {
		ret = ret + tree[index];
		index = index - shift(index);
	}
	
	return ret;
}

void preprocess() {
	sort(a + 1, a + n + 1, cp_1);
	int i, j;
	for (i = 1; i <= n; i++) {
		tmp[i] = a[i].age;
	}
	
	sort(tmp + 1, tmp + 1 + n);
	
	for (i = 1; i <= n; i++) {
		if (i == 1 || tmp[i] != tmp[i-1]) {
			disc.push_back(tmp[i]);
		}
	}
	
	for (i = 1, j = 1; i <= n; i++) {
		while (j <= n && a[j].rep <= a[i].rep) {
			add1(getlow(a[j].age));
			j++;
		}
		
		cont[a[i].id] = getsum(gethigh(a[i].age + k)) - getsum(getlow(a[i].age - k) - 1);
	}
	/*
	for (i = 1; i <= n; i++) {
		cout << cont[i] << endl;
	}*/
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return -1;
	if (start <= l && r <= end) {
		return rmq[index];
	}
	
	int mid = l + (r - l) / 2;
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

void update(int pt, int l, int r, int index, int val) {
	if (l > r) return;
	if (pt == l && pt == r) {
		rmq[index] = max(val, rmq[index]);
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
	
	rmq[index] = max(rmq[index * 2], rmq[index * 2 + 1]);
}

void solve() {
	sort(qr + 1, qr + q + 1, cp_2);
	int i, j;
	int m = (int) disc.size();
	for (i = 1, j = n; i <= q; i++) {
		while (j >= 1 && qr[i].y <= a[j].rep) {
			update(getlow(a[j].age), 1, m, 1, cont[a[j].id]);
			j--;
		}
		
		int left = min(b[qr[i].l].age, b[qr[i].r].age);
		int right = max(b[qr[i].l].age, b[qr[i].r].age);
		int l_index = getlow(right - k), r_index = gethigh(left + k);
		
		ans[qr[i].id] = query(l_index, r_index, 1, m, 1);
		if (ans[qr[i].id] < 2) {
			ans[qr[i].id] = -1;
		}
	}
	
	for (i = 1; i <= q; i++) {
		printf("%d\n", ans[i]);
	}
}

int main() {
	scanf("%d%d", &n, &k);
	int i;
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i].rep);
	}
	
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i].age);
		a[i].id = i;
		// make a copy of the person
		b[i] = a[i];
	}
	
	scanf("%d", &q);
	for (i = 1; i <= q; i++) {
		scanf("%d%d", &qr[i].l, &qr[i].r);
		qr[i].id = i;
		if (a[qr[i].l].rep > a[qr[i].r].rep) {
			swap(qr[i].l, qr[i].r);
		}
		qr[i].y = a[qr[i].r].rep;
	}
	
	preprocess();
	
	solve();
	
	return 0;
}
