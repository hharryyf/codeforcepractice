#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int N;
struct point{
  ll x , y;
} P[maxn];

unordered_map<int, int> s;

ll gcd(ll a, ll b) {
	if (a == 0) return b;
	return gcd(b % a, a);
}

ll correct(ll L, ll H) {
	if (L == 0 || H == 0) return 0;
	ll l = L / gcd(L, H), h = H / gcd(L, H);
	ll ret = 0;
	for (ll i = 0 ; i <= L-1; i++) {
		ret += h * i / l;
	}
	return ret;
}

ll query(ll length, ll height) { 
	// cout << "query " << length << " " << height << endl;
	if (length <= 1 || height <= 1) return 0;
	ll outter = length + 1 + height;
	ll ext = gcd(length, height) - 1;
	ll b = outter + ext;
	ll inner = (length * height - b + 2) / 2;
	// cout << inner + ext << " = " << inner << " + " << " ext= " << ext << endl;
	return inner + ext;
}

ll solve_1(vector<point> &pt, ll y) {
    ll ret = 0;
    int m = pt.size();
    for (int i = 1; i < m; i++) {
      ret += (pt[i].x - pt[i-1].x) * (min(pt[i].y, pt[i-1].y) -y);
      // cout << (pt[i].x - pt[i-1].x) * (min(pt[i].y, pt[i-1].y) -y) << endl;
      ret += query(pt[i].x - pt[i-1].x, abs(pt[i].y - pt[i-1].y));
    }
    return ret;
}

ll solve_2(vector<point> &pt, ll y) {
    ll ret = 0;
    int m = (int) pt.size();
    for (int i = 1; i < m; i++) {
      ret += (pt[i].x - pt[i-1].x) * (y - max(pt[i].y, pt[i-1].y));
      // cout << (pt[i].x - pt[i-1].x) * (y - max(pt[i].y, pt[i-1].y)) << endl;
      ret += query(pt[i].x - pt[i-1].x, abs(pt[i].y - pt[i-1].y));
    }
    return ret;
}

void unit_test() {
	int i, j = 0;
	
	for (i = 0 ; i < 1000; i++) {
		ll x = rand() % 10, y = rand() % 10;
		if (correct(x, y) == query(x, y)) {
			cout << "pass " << i << endl;
			j++;
		} else {
			cout << "fail " << i << endl;
			cout << x << " " << y << endl;
			cout << "correct is " << correct(x, y) << " get " << query(x, y) << endl;
		}
	}
	cout << "pass " << j << endl; 
	//cout << query(8, 9) << " correct " << correct(8, 9) << endl;
}

int main(){
	  // unit_test();
	  vector<point> up, down;
	  cin >> N;
	  for(int i = 1; i <= N; ++i){
		cin >> P[i].x >> P[i].y;
	  }
	  sort(P + 1 , P + 1 + N , [&](point& a , point& b){
		if(a.x == b.x)return a.y < b.y;
		return a.x < b.x;
	  });

	  for (int i = 1; i <= N; ++i) {
		if (P[i].x != P[1].x) break;
		s[P[i].y] = i;
	  }
	  int l = 1, r = N;
	  for (int i = N; i >= 1; i--) {
		if (P[i].x != P[N].x) break;
		if (s.find(P[i].y) != s.end()) {
		  l = s[P[i].y];
		  r = i;
		  break;
		}
	  }
	  up.push_back(P[l]);
	  down.push_back(P[l]);
	  for (int i = 1; i <= N; i++) {  
		if (i != l && i != r) {
		  if (P[i].y > P[l].y) {
		    up.push_back(P[i]);
		  } else {
		      down.push_back(P[i]);
		  }
		}
	  }

	  up.push_back(P[r]);
	  down.push_back(P[r]);

	  cout << solve_1(up, P[r].y) + solve_2(down, P[r].y) << endl;
	  return 0;
}
