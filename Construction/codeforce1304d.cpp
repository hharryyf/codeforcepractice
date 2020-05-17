#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

char st[MAX_SIZE];
int a[MAX_SIZE];
int b[MAX_SIZE];
int n;

int main() {
    int T;
    scanf("%d", &T);
    while (T > 0) {
        int i, j;
        list<int> val;
        scanf("%d", &n);
        for (i = 0; i < n; ++i) {
            val.push_back(i+1);
            a[i] = 0;
            b[i] = 0;
        }
        scanf("%s", st);
        for (i = n - 2; i >= 0; --i) {
            if ((i == 0 && st[i] == '<')|| (st[i] == '<' && st[i-1] == '>')) {
                for (j = i; j <= n - 2 && st[j] == '<'; ++j) {
                    a[j] = val.front();
                    val.pop_front();
                }
            }
        }

        for (i = 0 ; i < n; ++i) {
            if (a[i] == 0) {
                a[i] = val.back();
                val.pop_back();
            }
        }

        for (i = 0 ; i < n; ++i) {
            printf("%d ", a[i]);
        }
        printf("\n");

        for (i = 0; i < n; ++i) {
            val.push_back(i+1);
        }

        for (i = 0 ; i < n - 1; ++i) {
            if (st[i] == '<') {
                b[i] = val.front();
                val.pop_front();
            }
        }

        vector<int> ret;
        int index = -1;
        for (i = 0 ; i < n; ++i) {
            if (b[i] == 0) {
                ret.push_back(val.front());
                val.pop_front();
                if (index == -1) {
                    index = i;
                }
            } else if (!ret.empty()) {
                while (!ret.empty()) {
                    b[index++] = ret.back();
                    ret.pop_back();
                }
                index = -1;
            }
        }

        while (!ret.empty()) {
            b[index++] = ret.back();
            ret.pop_back();
        }
        
        index = -1;
        for (i = 0 ; i < n; ++i) {
            printf("%d ", b[i]);
        }
        printf("\n");
        --T;
    }
    return 0;
}