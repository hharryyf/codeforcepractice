#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
using namespace std;

struct Matrix {
	   ll a[3][3];
	   Matrix operator *(Matrix other) const {
	   		Matrix ret;
			int i, j, k;
			for (i = 0 ; i < 3; i++) {
				for (j = 0 ; j < 3; j++) {
					ret.a[i][j] = 0;
					for (k = 0 ; k < 3; k++) {
						ret.a[i][j] += a[i][k] * other.a[k][j];
						ret.a[i][j] %= MOD;
					}
				}
			}  
            return ret;		  
	   }
};

Matrix fastpow(Matrix x, ll p) {
	   Matrix base = x;
	   Matrix ret;
	   int i, j;
	   for (i = 0 ; i < 3; i++) {
	   	   for (j = 0 ; j < 3; j++) {
		   	   ret.a[i][j] = 1ll * (i == j);
		   }
	   }
	   while (p > 0) {
 		   if (p % 2 == 0) {
		   	  base = base * base;	
           	  p >>= 1;
		   } else {
		   	  ret = ret * base;
		   	  p--;
		   }
	   }	   		
	   return ret;	   
}

vector<ll> dotproduct(Matrix x, vector<ll> curr) {
    vector<ll> ret = vector<ll>(3, 0);
    int i, j;
    for (i = 0 ; i < 3; i++) {
		for (j = 0 ; j < 3; j++) {
			ret[i] += x.a[i][j] * curr[j];
			ret[i] %= MOD;
		}
	}
	return ret;
}

Matrix matrix[8];

void preprocess() {
	 int i, j;
	 for (i = 0 ; i < 8; i++) {
	 	 for (j = 0 ; j < 3; j++) {
		 	 if (j == 0 && (i & (1 << j))) {
			 	matrix[i].a[j][0] = matrix[i].a[j][1] = 1;
		     } 
		     
		     if (j == 1 && (i & (1 << j))) {
			 	matrix[i].a[j][0] = matrix[i].a[j][1] = matrix[i].a[j][2] = 1;
			 }
			 
			 if (j == 2 && (i & (1 << j))) {
			 	matrix[i].a[j][1] = matrix[i].a[j][2] = 1;
			 }
			 
         }
	 }
}


int cnt[3];
map<ll, vector<int> > add;
map<ll, vector<int> > del;
vector<ll> disc;
pair<pair<ll, ll>, int> block[10011];
ll tmp[20022];

int getid() {
	int i;
	int ret = 0;
	for (i = 0 ; i < 3; i++) {
		if (!cnt[i]) ret |= (1 << i);
	}
	return ret;
}

int main() {
	preprocess();
	vector<ll> ans = vector<ll>(3, 0);
	ans[1] = 1;
	int i, n, j = 0;
	ll m;
	scanf("%d%lld", &n, &m);
	for (i = 1; i <= n; i++) {
		scanf("%d%lld%lld", &block[i].second, &block[i].first.first, &block[i].first.second);
		block[i].second--;
		add[block[i].first.first].push_back(block[i].second);
		del[block[i].first.second].push_back(block[i].second);
		tmp[j++] = block[i].first.first;
		tmp[j++] = block[i].first.second;
	}
	sort(tmp, tmp + j);
	for (i = 0 ; i < j; i++) {
		if (i == 0 || tmp[i] != tmp[i-1]) {
		   disc.push_back(tmp[i]);
		}
	}
	
	ll curr = 1;
	ans = dotproduct(fastpow(matrix[getid()], disc[0] - 2), ans);
	curr = disc[0] - 1;
	int sz = (int) disc.size();
	for (i = 0; i < sz; i++) {
		for (auto v : add[disc[i]]) {
			cnt[v]++;
		}
		
		
		ans = dotproduct(matrix[getid()], ans);
		curr = disc[i];
		
		for (auto v : del[disc[i]]) {
			cnt[v]--;
		}
		
		if (i == sz-1) {
		    ans = dotproduct(fastpow(matrix[getid()], m - curr), ans);
		} else {
			ans = dotproduct(fastpow(matrix[getid()], disc[i+1] - 1 - curr), ans);
			curr = disc[i+1] - 1;
		}
		// cout << disc[i] << ": " << ans[0] << " " << ans[1] << " " << ans[2] << endl;
	}
	
	cout << ans[1] % MOD << endl;
	return 0;
}

