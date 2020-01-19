#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define BLOCK_SIZE 400
using namespace std;

struct sqrtdecomp {
    struct block {
        int h[100001];
        deque<int> q;
    };
    
    int n;
    int block_size = 1;
    block chunk[BLOCK_SIZE + 2];
    
    void init(int nele, int a[]) {
        int i;
        this->n = nele;
        this->block_size = sqrt(n);
        for (i = 0 ; i < n; i++) {
            int bid = i / block_size;
            chunk[bid].q.push_back(a[i]);
            chunk[bid].h[a[i]]++;
        }
    }
    
    // this is just a debug function
    void show() {
        int i;
        
        for (i = 0 ; i <= n / block_size; i++) {
            for (auto nq : chunk[i].q) {
                printf("%d ", nq);
            }
		}
		printf("\n");
    }
    
    void update(int l, int r) {
        int L = l / block_size, R = r / block_size;
        int Lid = l % block_size, Rid = r % block_size;
        deque<int> :: iterator iter;
        // L, R are incomplete [L+1, R-1] are complete chunk
        if (L == R) {
            iter = chunk[L].q.begin() + Rid;
            int v = *iter;
            chunk[L].q.erase(iter);
            iter = chunk[L].q.begin() + Lid;
            chunk[L].q.insert(iter, v);
        } else {
		    int i;
            for (i = L; i <= R-1; i++) {
                int v = chunk[i].q.back();
                chunk[i+1].q.push_front(v);
                chunk[i+1].h[v]++;
                chunk[i].q.pop_back();
                chunk[i].h[v]--;
            }
            
            iter = chunk[R].q.begin() + Rid + 1;
            int v = *iter;
            chunk[R].h[v]--;
            chunk[R].q.erase(iter);
            iter = chunk[L].q.begin() + Lid;
            chunk[L].q.insert(iter, v);
            chunk[L].h[v]++;
        }
    }
    
    int query(int l, int r, int k) {
        int L = l / block_size, R = r / block_size;
        int Lid = l % block_size, Rid = r % block_size;
        int ret = 0;
        deque<int>::reverse_iterator rit = chunk[L].q.rbegin();
        deque<int>::iterator iter = chunk[R].q.begin();
        int i = block_size - 1;
        if (L == R) {
		   i = 0;
		   while (iter != chunk[R].q.end()) {
		   		if (i >= Lid && i <= Rid && *iter == k) {
		           ret++;
				} 
		   		i++, iter++;
		   }
		} else {
	        while (rit != chunk[L].q.rend()) {
	            if (i < Lid) break;
	            if (*rit == k) ret++;
	            i--, rit++;
	        }
	        
	        i = 0;
	        while (iter != chunk[R].q.end()) {
	            if (i > Rid) break;
	            if (*iter == k) ret++;
	            i++, iter++;
	        }
	        
	        for (i = L + 1; i <= R - 1; i++) {
	            ret += chunk[i].h[k];
	        }
    	}
        return ret;
    }
};

sqrtdecomp s;
int arr[BLOCK_SIZE * BLOCK_SIZE];

int main() {
    int i, n;
    scanf("%d", &n);
    for (i = 0 ; i < n; i++) scanf("%d", &arr[i]);
    s.init(n, arr);
    int q;
    int lst = 0;
    scanf("%d", &q);
    while (q > 0) {
        int tp;
        int l, r, k;
        scanf("%d", &tp);
        if (tp == 1) {
            scanf("%d%d", &l, &r);
            #ifndef DEBUG
            l = (l + lst - 1) % n, r = (r + lst - 1) % n;
            #endif
            if (l > r) swap(l, r);
            s.update(l, r);
            #ifdef DEBUG
            s.show();
            #endif
        } else {
            scanf("%d%d%d", &l, &r, &k);
            #ifndef DEBUG
            l = (l + lst - 1) % n, r = (r + lst - 1) % n, k = (k + lst - 1) % n + 1;
            #endif
            if (l > r) swap(l, r);
            lst = s.query(l, r, k);
            printf("%d\n", lst);
        }
        
        q--;
    }
    return 0;
}
