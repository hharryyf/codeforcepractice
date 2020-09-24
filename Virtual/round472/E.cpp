#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 100111
typedef long long ll;
using namespace std;

struct fraction {
    ll num, den;
    fraction(ll num = 1, ll den = 1) {
        this->num = num, this->den = den;
        this->reduce();
    }

    bool operator ==(fraction other) const {
        return other.den * num == other.num * den;
    }

    fraction operator +(fraction other) const {
        fraction ret;
        ret.num = other.den * num + other.num * den;
        ret.den = other.den * den;
        ret.reduce();
        return ret;   
    }

    fraction operator -(fraction other) const {
        other.num *= -1;
        fraction ret = fraction(num, den);
        ret = ret + other;
        ret.reduce();
        return ret;
    }

    void reduce() {
        ll g = __gcd(llabs(num), llabs(den));
        num /= g, den /= g;
        if (num < 0 && den < 0) {
            num *= -1, den *= -1;
        } else if (den < 0 && num > 0) {
            den *= -1, num *= -1;
        }

        if (num == 0) den = 1;
    }

    fraction operator *(fraction other) const {
        fraction ret;
        ret.num = other.num * num;
        ret.den = other.den * den;
        ret.reduce();
        return ret;
    }

    fraction operator /(fraction other) const {
        fraction ret = fraction(other.den * num, other.num * den);
        ret.reduce();
        return ret;
    }

    bool operator < (fraction other) const {
        return other.den * num < other.num * den;
    }

    bool operator > (fraction other) const {
        return other.den * num > other.num * den;
    }

    bool operator <= (fraction other) const {
        return other.den * num <= other.num * den;
    }

    bool operator >= (fraction other) const {
        return other.den * num >= other.num * den;
    }

    bool operator !=(fraction other) const {
        return other.den * num != other.num * den;
    }
};

pair<fraction, fraction> vc[MAX_SIZE];
fraction tmp[MAX_SIZE];

static bool cmp(const pair<fraction, fraction> &f1, const pair<fraction, fraction> &f2) {
    if (f1.first != f2.first) return f1.first < f2.first;
    return f1.second > f2.second;
}

ll divc(int l, int r) {
	if (l == r) return 0ll;
	if (l > r) return 0ll;
	int mid = l + (r - l) / 2;
	ll L = divc(l, mid), R = divc(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	ll cross = 0ll;
	while (i <= mid && j <= r) {
		if (vc[i].second < vc[j].second) {
			tmp[k++] = vc[i++].second;
		} else {
			tmp[k++] = vc[j++].second;
			cross += (ll) (mid - i + 1);
		}
	}
	
	while (i <= mid) tmp[k++] = vc[i++].second;
	while(j <= r) tmp[k++] = vc[j++].second;
	for (i = l; i <= r; i++) vc[i].second = tmp[i];
	return L + R + cross;
}

int main() {
    int n, w;
    int i;
    scanf("%d%d", &n, &w);
    for (i = 1; i <= n; ++i) {
        int x, v;
        scanf("%d%d", &x, &v);
        vc[i].first = fraction(x, v - w);
        vc[i].second = fraction(x, v + w);
    }

    sort(vc + 1, vc + 1 + n, cmp);
    cout << divc(1, n) << endl;
    return 0;
}