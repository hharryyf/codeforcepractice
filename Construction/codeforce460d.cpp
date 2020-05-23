#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<ll> p2;

void preprocess() {
    p2.push_back(1);
    while (p2.back() * 2 + 1ll <= 1000000000000ll) {
        p2.push_back(p2.back() * 2 + 1ll);
    }
}
/*
    We have a key observation, if k >= 5
    the answer is 0, since for all even numbers
    x ^ (x+1) = 1 holds
*/

int main() {
    ll L, R, k;
    int i;
    cin >> L >> R >> k;
    preprocess();
    if (k == 1) {
        cout << L << endl;
        cout << 1 << endl;
        cout << L << endl;
    } else if (k == 2) {
        if (R - L + 1 == 2) {
            if ((L ^ (L+1)) < L) {
                cout << (L ^ (L + 1)) << endl;
                cout << 2 << endl;
                cout << L << " " << L + 1 << endl;
            } else {
                cout << L << endl;
                cout << 1 << endl;
                cout << L << endl;
            }
        } else {
            if (L % 2 == 0) {
                cout << 1 << endl;
                cout << 2 << endl;
                cout << L << " " << L + 1 << endl;
            } else {
                cout << 1 << endl;
                cout << 2 << endl;
                cout << L + 1 << " " << L + 2 << endl;
            }
        }
    } else if (k > 4) {
        cout << 0 << endl;
        cout << 4 << endl;
        if (L % 2 == 0) {
            cout << L << " " << L + 1 << " " << L + 2 << " " << L + 3 << endl;
        } else {
            cout << L + 1 << " " << L + 2 << " " << L + 3 << " " << L + 4 << endl;
        }
    } else if (k == 4) {
        if (R - L + 1 > 4) {
            cout << 0 << endl;
            cout << 4 << endl;
            if (L % 2 == 0) {
                cout << L << " " << L + 1 << " " << L + 2 << " " << L + 3 << endl;
            } else {
                cout << L + 1 << " " << L + 2 << " " << L + 3 << " " << L + 4 << endl;
            }
        } else {
            // if k=4 and r - l + 1=4 simply use brute force
            // check all subsets
            int bestmask = 15;
            ll ret = 0;
            vector<ll> can;
            can.push_back(L), can.push_back(L+1), can.push_back(L+2), can.push_back(L+3);
            ret ^= L, ret ^= (L+1), ret ^= L+2, ret ^= L+3;
            for (i = 1; i <= 14; ++i) {
                ll ret2 = 0;
                for (int j = 0 ; j < 4; ++j) {
                    if ((1 << j) & i) {
                        ret2 ^= can[j];
                    }
                }

                if (ret2 < ret) {
                    ret = ret2;
                    bestmask = i;
                }
            }
            cout << ret << endl;
            cout << __builtin_popcount(bestmask) << endl;
            for (i = 0 ; i < 4; ++i) {
                if (bestmask & (1 << i)) {
                    cout << can[i] << " ";
                }
            }
            cout << endl;
        }   
    } else {
        // the trickist case, k=3, this should be dealt properly
        // we have a default answer 1, see whether we can have a better answer
        ll start = -1;
        for (auto v : p2) {
            if ((v + 1) * 3 / 2 <= R && v >= L) {
                start = v;
            }
        }

        if (start != -1) {
            cout << 0 << endl;
            cout << 3 << endl;
            cout << start << " " << (start + 1) * 3 / 2 - 1 << " " << (start + 1) * 3 / 2 << endl; 
        } else {
            cout << 1 << endl;
            cout << 2 << endl;
            if (L % 2 == 0) {
                cout << L << " " << L + 1 << endl;
            } else {
                cout << L + 1 << " " << L + 2 << endl;
            }
        }
    }
    return 0;
}