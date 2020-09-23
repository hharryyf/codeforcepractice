#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> prime;
int visited[MAX_SIZE];
set<int> st;
int n;

int logs(int base, int num) {
    int ret = 0;
    while (num >= base) {
        ret++;
        num /= base;
    }
    return ret;
}

void del(int base) {
    int i;
    printf("B %d\n", base);
    for (i = 1; i * base <= n; ++i) {
        st.erase(i * base);
    }

    fflush(stdout);
    scanf("%d", &i);
}

int query(int base) {
    int ret;
    printf("A %d\n", base);
    fflush(stdout);
    scanf("%d", &ret);
    return ret;
}

int pw(int base, int p) {
    int ret = 1;
    while (p > 0) {
        ret = ret * base;
        p--;
    }
    return ret;
}

int main() {
    int i, j, ans = 1;
    scanf("%d", &n);
    for (i = 2; i <= n; ++i) {
        if (visited[i]) continue;
        prime.push_back(i);
        for (j = 1; j * i <= n; ++j) {
            visited[i * j] = 1;
        }
    }
    // for (i = 0 ; i < 25; ++i) cout << prime[i] << " ";
    for (i = 1; i <= n; ++i) st.insert(i);
    // step 1: eliminate the primes of sqrt
    int idx = lower_bound(prime.begin(), prime.end(), (int) sqrt(n) + 1) - prime.begin(), sz = prime.size();
    // cout << idx << endl;
    vector<int> large;
    for (i = idx; i < sz; ++i) {
        large.push_back(prime[i]);
    }
    sz = (int) large.size();
    int block_size = sqrt(sz);
    for (i = 0 ; i < sz; ++i) {
        int L = i * block_size, R = min(sz - 1, L + block_size - 1);
        if (L > R) break;
        for (j = L; j <= R; ++j) {
            del(large[j]);
        }

        int ret = query(1);
        // this means there's a prime factor in block [L, R]
        if (ret != (int) st.size()) {
            for (j = L; j <= R; ++j) {
                if (query(large[j]) == 1) {
                    ans *= large[j];
                    break;
                }
            }
            break;
        }
    }

    
    // step 2, for the small prime factors, use binary search to get the solution
    for (i = 0 ; i < idx; ++i) {
        del(prime[i]);
        int low = 1, high = logs(prime[i], n), fac = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (query(pw(prime[i], mid)) == 1) {
                fac = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        ans = ans * pw(prime[i], fac);
    }
    printf("C %d\n", ans);
    fflush(stdout);
    return 0;
}