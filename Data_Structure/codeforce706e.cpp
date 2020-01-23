#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

struct node {
    int value;
    node *next, *down;
    node(int val) {
        value = val;
    }
};

node *l[MAX_SIZE][MAX_SIZE];
int n, m;
node *getpt(int x, int y) {
    node *ret = l[0][0];
    int i;
    for (i = 0 ; i < x; i++) {
        ret = ret->down;
    }
    
    for (i = 0 ; i < y; i++) {
        ret = ret->next;
    }
    return ret;
}

int main() {
    int i, j, n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (i = 0 ; i <= n + 1; i++) {
        for (j = 0 ; j <= m + 1; j++) {
            if (i >= 1 && j >= 1 && i <= n && j <= m) {
                int v;
                scanf("%d", &v);
                l[i][j] = new node(v);
            } else {
			    l[i][j] = new node(-1);
			}
        }
    }
    
    for (i = 0 ; i <= n + 1; i++) {
        for (j = 0 ; j <= m + 1; j++) {
            l[i][j]->down = l[i+1][j];
            l[i][j]->next = l[i][j+1];
        }
    }
    
    while (q > 0) {
        int a, b, c, d, w, h;
        scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &h, &w);
        node *p1 = getpt(a-1, b-1), *p2 = getpt(c-1, d-1);
        node *p3 = p1->next, *p4 = p1->down, *p5 = p2->next, *p6 = p2->down;
		for (i = 0 ; i < w; i++) {
            swap(p3->down, p5->down);
			if (i != w-1) {
                p3 = p3->next, p5 = p5->next;
            }
        }
        p3 = p3->down, p5 = p5->down;
        
        for (i = 0 ; i < h; i++) {
            swap(p3->next, p5->next);
			if (i != h-1) {
                p3 = p3->down, p5 = p5->down;
            }
        }
        
        for (i = 0 ; i < h; i++) {
            swap(p4->next, p6->next);
            if (i != h-1) {
                p4 = p4->down, p6 = p6->down;
            }
        }
        p4 = p4->next, p6 = p6->next;
        for (i = 0 ; i < w; i++) {
            swap(p4->down, p6->down);
			if (i != w-1) {
                p4 = p4->next, p6 = p6->next;
            }
        }
        q--;
    }
    
    for (i = 1 ; i <= n; i++) {
        node *curr = l[i][0];
        for (j = 0; j <= m; j++) {
            if (j != 0) {
                printf("%d ", curr->value);
            }
            curr = curr->next;
        }
        printf("\n");
    }
    return 0;
}
