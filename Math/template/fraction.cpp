#include <bits/stdc++.h>
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
        if (other.num == num && num == 0) return 0;
        if (num < 0 && other.num < 0) {
            return num * other.den > den * other.num;
        } else if (num >= 0 && other.num >= 0) {
            return num * other.den < den * other.num;
        } else if (num < 0 && other.num >= 0) {
            return 1;
        } 

        return 0;
    }

    bool operator !=(fraction other) const {
        return other.den * num != other.num * den;
    }
};



int main() {
    fraction f1 = fraction(4, 24), f2 = fraction(1, 1);
    auto f = f1 + f2;
    cout << f.num << "/" << f.den << endl;
    return 0;
}