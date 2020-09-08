#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;
typedef long long ll;

struct rolling_hash {
    ll val[MAX_SIZE];
    ll ep[MAX_SIZE];
    ll mod = 1e9 + 9;
    int base = 47;
    int N;
    void init(int base=47, ll mod=1e9+9) {
        int i;
        this->base = base, this->mod = mod;
        ep[0] = 1;
        for (i = 1; i < MAX_SIZE; ++i) {
            ep[i] = ep[i-1] * base;
            ep[i] %= mod; 
        }
    }

    void calc(char st[], int N) {
        this->N = N;
        for (int i = 1 ; i <= N; ++i) {
            val[i] = val[i-1] * base + (st[i] - 'a');
            val[i] %= mod;
        }
    }

    ll decode(int l, int r) {
        ll valL = val[l-1] * ep[r - l + 1];
        ll valR = val[r];
        return ((valR - valL) % mod + mod) % mod;
    }

    bool equal(int l1, int r1, int l2, int r2) {
        if (r1 - l1 != r2 - l2) return false;
        return decode(l1, r1) == decode(l2, r2);
    }
};

rolling_hash h[26];
char st[MAX_SIZE];
char tmp[MAX_SIZE], tmp2[MAX_SIZE];
char pt[MAX_SIZE];
int nxt[MAX_SIZE][26];
int focc[26];
ll hval[26];
pair<int, int> ord[26];
vector<pair<int, int>> org;
vector<pair<ll, int>> pthash;
vector<pair<ll, int>> gen(int l, int r) {
    int i;
    vector<pair<ll, int>> ret;
    for (i = 0; i < 26; ++i) {
        ord[i].first = nxt[l][i];
        ord[i].second = i;
    }

    sort(ord, ord + 26);
    for (i = 0 ; i < 26; ++i) {
        if (ord[i].first <= r) {
            ret.emplace_back(h[ord[i].second].decode(l, r), ord[i].second);
        }
    }

    return ret;
}

ll calc(char ss[], int base, ll mod) {
    ll ret = 0;
	int N = strlen(ss+1);
    for (int i = 1 ; i <= N; ++i) {
        ret = ret * base + (ss[i] - 'a');
        ret %= mod;
    }
	return ret;
}

vector<int> ans;
int main() {
    int i, j, N, M;
    scanf("%d%d", &N, &M);
    scanf("%s", st + 1);
	scanf("%s", pt + 1);
	for (j = 0 ; j < 26; ++j) {
        for (i = 1 ; i <= N; ++i) {
            if (st[i] == j + 'a') {
                tmp[i] = 'b';
            } else {
                tmp[i] = 'a';
            }
        }

        h[j].init();
        h[j].calc(tmp, N);
    }

	for (j = 0 ; j < 26; ++j) {
		for (i = 1; i <= M; ++i) {
			if (pt[i] == j + 'a') {
				tmp2[i] = 'b';
				if (focc[j] == 0) {
					focc[j] = i;
				}
			} else {
				tmp2[i] = 'a';
			}
		}

		hval[j] = calc(tmp2, 47, 1e9+9);
	}

    for (i = N; i >= 1; --i) {
        for (j = 0 ; j < 26; ++j) {
            if (st[i] == 'a' + j) {
                nxt[i][j] = i;
            } else {
                if (i == N) {
                    nxt[i][j] = N + 1;
                } else {
                    nxt[i][j] = nxt[i+1][j];
                }
            }
        }
    }

	for (i = 0 ; i < 26; ++i) {
		if (focc[i] > 0) {
			org.emplace_back(focc[i], i);
		}
	}

	sort(org.begin(), org.end());
	for (auto p : org) {
		pthash.emplace_back(hval[p.second], p.second);
		// cout << hval[p.second] << " " << p.second << endl;
	}

	if (N < M) {
		printf("0\n");
		return 0;
	}

	for (i = 1; i <= N - M + 1; ++i) {
		auto vc = gen(i, i + M - 1);
		if (vc.size() != pthash.size()) {
			continue;
		}
/*
		for (auto v : vc) {
			cout << v.first << " " << v.second << endl;
		}
		cout << "finish" << endl;
		*/
		bool valid = true;
		map<int, int> mp;
		// cout << " start " << endl;
		for (j = 0 ; j < (int) vc.size(); ++j) {
			if (pthash[j].first != vc[j].first) {
				valid = false;
				break;
			}
			int v1 = vc[j].second, v2 = pthash[j].second;
			if (mp.find(v1) != mp.end() && mp[v1] != v2) {
				valid = false;
				break;
			}

			if (mp.find(v2) != mp.end() && mp[v2] != v1) {
				valid = false;
				break;
			}

			mp[v1] = v2, mp[v2] = v1;
		}

		if (!valid) {
			continue;
		}

		if (valid) {
			ans.push_back(i);
		}
	}

	printf("%d\n", (int) ans.size());
	for (auto v : ans) {
		printf("%d ", v);
	}
    return 0;
}