#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
int N;
char st[MAX_SIZE], pt[MAX_SIZE];
int f[MAX_SIZE];
vector<pair<char, char>> edg;

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void unionset(int x, int y) {
	int a = find(x), b = find(y);
	f[a] = b;
}

int main() {
	int i;
	scanf("%d", &N);
	scanf("%s", st);
	scanf("%s", pt);
	for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
	for (i = 0 ; i < N; ++i) {
		if (find(st[i] - 'a') != find(pt[i] - 'a')) {
			edg.emplace_back(st[i], pt[i]);
			unionset(st[i] - 'a', pt[i] - 'a');
		}
	}

	cout << edg.size() << endl;
	for (auto e : edg) {
		cout << e.first << " " << e.second << endl;
	}
	return 0;
}
