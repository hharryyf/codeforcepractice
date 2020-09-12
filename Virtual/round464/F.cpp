#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

int N, K, L[101], R[101], f[MAX_SIZE], g0[MAX_SIZE], g1[MAX_SIZE], g2[MAX_SIZE];
deque<int> q;

int F(int x) {
	return x < 0 || x > N ? MAX_SIZE : f[x];
}

int main() {
    int i, j;
	scanf("%d%d", &N, &K);
	for (i = 1; i <= K; i++)
		scanf("%d%d", &L[i], &R[i]);
	for (i = 1; i <= N; i++) f[i] = MAX_SIZE;
	for (i = 1; i <= K; i++) {
		for (j = 0; j <= N; j++) {
			g0[j] = F(j - R[i] + R[i - 1]);
        }
		
        for (j = 0; j <= N; j++) {
			while (!q.empty() && F(q.back()) >= F(j - L[i] + R[i - 1])) q.pop_back();
			q.push_back(j - L[i] + R[i - 1]);
			while (!q.empty() && q.front() < j - R[i] + R[i - 1]) q.pop_front();
			g2[j] = F(q.front());
		}
        
        for (int j = 0; j <= N; j++) {
			while (!q.empty() && F(q.back()) >= F(R[i - 1] - j)) q.pop_back();
            q.push_back(R[i - 1] - j);
			while (!q.empty() && q.front() > R[i - 1] - j + R[i] - L[i]) q.pop_front();
			g1[j] = F(q.front());
		}
		for (int j = 0; j <= N; j++)
			f[j] = min(min(g0[j], g1[j] + 1), g2[j] + 2);
	}
	if (F(R[K] - N) >= MAX_SIZE) {
		printf("Hungry\n");
    } else {
		printf("Full\n%d\n", F(R[K] - N));
    }

	return 0;
}