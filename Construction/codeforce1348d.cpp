#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T > 0) {
        vector<int> disc;
        int n, i = 1;
        scanf("%d", &n);
        while (n >= i) {
            disc.push_back(i);
            n -= i;
            i <<= 1;            
        }

        if (n > 0) {
            disc.push_back(n);
        }
        sort(disc.begin(), disc.end());
        printf("%d\n", (int) disc.size() - 1);
        for (i = 1; i < (int) disc.size(); ++i) {
            printf("%d ", disc[i] - disc[i-1]);
        }
        printf("\n");
        --T;
    }
    return 0;
}