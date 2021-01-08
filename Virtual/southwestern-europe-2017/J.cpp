#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

ll A[MAX_SIZE], B[MAX_SIZE];
ll tol[3];
int N;

int main() {
    int i, j;
    
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        cin >> A[i];
    }

    for (i = 1; i <= N; ++i) {
        cin >> B[i];
    }

    for (i = 1; i <= N; ++i) {
        if (i <= 3) continue;
        A[i] = A[i] + A[i-3];
    }

    for (i = 1; i <= N; ++i) {
        for (j = 0; j < 3; ++j) {
            int desired = ((j - i) % 3 + 3) % 3;
            int nxt = N;
            while (nxt >= N - 3) {
                if (nxt % 3 == desired) {
                    break;
                }
                nxt--;
            }

            tol[j] += B[i] * A[nxt];
        }
    }

    for (i = 0 ; i < 3; ++i) {
        cout << tol[i] << " ";
    }
    cout << endl;
    return 0;
}