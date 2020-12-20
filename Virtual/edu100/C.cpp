#include <iostream>
#define INF (1<<30)
#define ID if (0)
using namespace std;

int cases, n, t, x;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> cases;
	while (cases--) {
		cin >> n;
		int answer = 0;
		int time = 0;
		int at = 0;
		int dest = INF;
		int desire = INF;
		for (int i = 1; i <= n; i++) {
			cin >> t >> x;
			if (at == desire) {
				answer += 1;
				desire = INF;
			}
			int delta = t-time;
			if (dest != INF) {
				if (abs(at-dest) <= delta) {
					if (desire >= min(at, dest) && desire <= max(at, dest)) {
						answer += 1;
						desire = INF;
					}
					at = dest;
					dest = INF;
				} else {
					if (dest>at) {
						if (desire >= at && desire <= (at+delta)) {
							answer += 1;
							desire = INF;
						}
						at += delta;
					}
					else {
						if (desire <= at && desire >= (at-delta)) {
							answer += 1;
							desire = INF;
						}
						at -= delta;
					}
				}
			}
			if (dest == INF) {
				dest = x;
			}
			time = t;
			desire = x;
			ID {
				printf("time,at=%d,%d\n", time, at);
			}
		}
		if (desire >= min(at, dest) && desire <= max(at, dest)) {
			answer += 1;
			desire = INF;
		}
		cout << answer << endl;
	}
}
