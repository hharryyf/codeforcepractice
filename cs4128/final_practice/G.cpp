#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100011;
int N;
struct point{
  ll x , y;
} P[maxn];

ll gcd(ll a, ll b) {
	if (a == 0) return b;
	return gcd(b % a, a);
}

ll correct(ll L, ll H) {
	if (L == 0 || H == 0) return 0;
	ll ret = 0;
	for (int i = 0 ; i < L; i++) {
		ret += H * i / L ;
	}
	return ret;
}

ll query(ll length, ll height) { 
	if (length == 0 || height == 0) return 0;
	ll outter = length + 1 + height;
	ll ext = gcd(length, height) - 1;
	ll b = outter + ext;
	ll inner = (length * height - b + 2) / 2;
	return inner + ext;
}

ll solve_1(vector<point> &pt, ll y) {
    ll ret = 0;
    int m = (int) pt.size();
    for (int i = 1; i < m; i++) {
      ret += (pt[i].x - pt[i-1].x) * (min(pt[i].y, pt[i-1].y) -y);
      ret += query(pt[i].x - pt[i-1].x, abs(pt[i].y - pt[i-1].y));
    }
    return ret;
}

ll solve_2(vector<point> &pt, ll y) {
    ll ret = 0;
    int m = (int) pt.size();
    for (int i = 1; i < m; i++) {
      ret += (pt[i].x - pt[i-1].x) * (y - max(pt[i].y, pt[i-1].y));
      ret += query(pt[i].x - pt[i-1].x, abs(pt[i].y - pt[i-1].y));
    }
    return ret;
}

void unit_test() {
	int i, j = 0;
	srand(time(NULL));
	for (i = 0 ; i < 100; i++) {
		ll x = rand() % 100000, y = rand() % 100000;
		if (correct(x, y) == query(x, y)) {
			j++;
		} else {
			cout << "fail " << i << endl;
			cout << x << " " << y << endl;
			cout << "correct is " << correct(x, y) << " get " << query(x, y) << endl;
			break;
		}
	}
}

static bool cmp(point &a, point &b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

map<ll, vector<int> > uu, dn;

int main(){
	 // unit_test();
	 map<ll, int> s;
	 vector<point> up, down;
	 cin >> N;
	 for(int i = 1; i <= N; ++i){
		cin >> P[i].x >> P[i].y;
	 }
	 
	 sort(P + 1 , P + 1 + N , cmp);

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
		    uu[P[i].x].push_back(P[i].y);
		  } else {
		      dn[P[i].x].push_back(P[i].y);
		  }
		}
	 }
     
    map<ll, vector<int> > :: iterator iter = uu.begin();
    while (iter != uu.end()) {
    	if (iter->first == P[r].x) {
    		for (int i = (int) iter->second.size() - 1; i >= 0; i--) {
    			up.push_back(point{iter->first, iter->second[i]});
    		}
    	} else {
    		for (int i = 0; i < (int) iter->second.size(); i++) {
    			up.push_back(point{iter->first, iter->second[i]});
    		}
    	}
    	iter++;
    }
     
    iter = dn.begin();
    while (iter != dn.end()) {
    	if (iter->first == P[l].x) {
    		for (int i = (int) iter->second.size() - 1; i >= 0; i--) {
    			down.push_back(point{iter->first, iter->second[i]});
    		}
    	} else {
    		for (int i = 0; i < (int) iter->second.size(); i++) {
    			down.push_back(point{iter->first, iter->second[i]});
    		}
    	}
    	iter++;
    } 
     
     
	 up.push_back(P[r]);
	 down.push_back(P[r]);
	 
	 /*
	 for (auto pp : up) {
	 	cout << pp.x << " " << pp.y << endl;
	 }
	 
	 cout << endl;
	 
	 for (auto pp : down) {
	 	cout << pp.x << " " << pp.y << endl;
	 }
	 
	 cout << endl;
	 */
	 cout << solve_1(up, P[r].y) + solve_2(down, P[r].y) << endl;
	 return 0;
}
