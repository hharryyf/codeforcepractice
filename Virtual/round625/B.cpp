#include <bits/stdc++.h>
#define int int64_t
using namespace std;
int n, b;
map<int, int> slices;
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int answer = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> b;
        slices[b-i] += b;
        answer = max(answer, slices[b-i]);
    }
    cout << answer << endl;
}