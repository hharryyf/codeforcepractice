#include <bits/stdc++.h>
#define MAX_SIZE 2001111
using namespace std;

vector<int> prime;
int visited[MAX_SIZE];

void SIEVE() {
    int i, j;
    for (i = 2; i <= 2000000; ++i) {
        if (!visited[i]) {
            prime.push_back(i);
            for (j = 1; j * i <= 2000000; ++j) {
                visited[i * j] = 1; 
            }
        }
    }
}

int a[1111];

void printvc(vector<int> &ret) {
    printf("%d\n", (int) ret.size());
    for (auto v : ret) {
        printf("%d ", v);
    }
    printf("\n");
}

int main() {
    int i, n, j;
    scanf("%d", &n);
    SIEVE();
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    sort(a + 1, a + 1 + n);
    vector<int> ret, ret2;
    for (i = 1; i <= n; ++i) {
        if (a[i] == 1) {
            ret.push_back(1);
        }
    }

    if (!ret.empty()) {
        for (i = 1; i <= n; ++i) {
            if (a[i] != 1 && binary_search(prime.begin(), prime.end(), a[i] + 1)) {
                ret.push_back(a[i]);
                break;
            }
        }
    }
    
    for (i = 1; i <= n; ++i) {
        for (j = i + 1; j <= n; ++j) {
            if (binary_search(prime.begin(), prime.end(), a[i] + a[j])) {
                ret2.push_back(a[i]);
                ret2.push_back(a[j]);
                break;
            }
        }
        if (!ret2.empty()) break;
    }

    if (ret.empty() && ret2.empty()) {
        ret.push_back(a[1]);
    }

    if (ret.size() > ret2.size()) {
        printvc(ret);
    } else {
        printvc(ret2);
    }
    return 0;
}