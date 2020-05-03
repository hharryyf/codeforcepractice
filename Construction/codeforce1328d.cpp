#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
int a[MAX_SIZE];
int ans[MAX_SIZE];
int main() {
    int i, q, n;
    scanf("%d", &q);
    while (q > 0) {
        scanf("%d", &n);
        bool flag = true;
        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            if (i > 1 && a[i] != a[i-1]) flag = false;
        }

        if (flag) {
            printf("1\n");
            for (i = 1; i <= n; ++i) {
                printf("1 ");
            }
            printf("\n");
        } else {
            if (n % 2 == 0) {
                printf("2\n");
                for (i = 1; i <= n; ++i) {
                    printf("%d ", i % 2 + 1);
                }
                printf("\n");
            } else  {
                int pos = -1;
                for (i = 1; i <= n; ++i) {
                    if (i > 1 && a[i] == a[i-1]) {
                        pos = i;
                        break;
                    }
                }

                if (pos != -1) {
                    ans[pos - 1] = ans[pos] = 1;
                    int j = 2;
                    for (i = pos + 1; i <= n; ++i) {
                        ans[i] = j;
                        j = j % 2 + 1;
                    }

                    for (i = 1; i < pos - 1; ++i) {
                        ans[i] = j;
                        j = j % 2 + 1;
                    }   
                    printf("2\n");
                    for (i = 1; i <= n; ++i) {
                        printf("%d ", ans[i]);
                    } 
                    printf("\n");
                } else {
                    printf("3\n");
                    for (i = 1; i <= n - 1; ++i) {
                        printf("%d ", i % 2 + 1);
                    }
                    printf("3\n");
                }
            }
        }
        --q;
    }
    return 0;
}