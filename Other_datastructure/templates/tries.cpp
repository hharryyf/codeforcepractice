#include <bits/stdc++.h>

using namespace std;

long long rt = 0ll;

struct node {
	struct node *child[10];
	bool isend;
	node() {
		this->isend = false;
		for (int i = 0 ; i < 10; i++) this->child[i] = NULL;
	}
};

node *insertion(node *t, vector<int> &vec, int pos) {
	if (pos == (int) vec.size()) {
		if (t == NULL) {
			t = new node();
		}
		t->isend = true;
		return t;
	}	
	
	if (t->child[vec[pos]] == NULL) {
		t->child[vec[pos]] = new node();
	}
	
	t->child[vec[pos]] = insertion(t->child[vec[pos]], vec, pos + 1);
	return t;
}

void findans(node *t, vector<int> &vec, int pos) {
	if (t == NULL) return;
	if ((int) vec.size() == pos) return;
	int res = -1;
	int index = -1;
	for (int i = 0 ; i < 10; i++) {
		if (t->child[i] != NULL && (i + vec[pos]) % 10 >= res) {
			index = i;
			res = (i + vec[pos]) % 10;
		}
	}
	
	if (index == -1) return;
	rt =  10ll * rt + ((long long) ((index + vec[pos]) % 10));
	findans(t->child[index], vec, pos + 1);
}

vector<int> token(long long num) {
	string str = to_string(num);
	vector<int> ret = vector<int>(19, 0);
	int i, j = (int) str.length() - 1;
	for (i = 18; i >= 0 && j >= 0; i--, j--) {
		ret[i] = (str[j] - '0');
	}
	
	return ret;
}


node *root = NULL;

vector<long long> allnum;

long long addition(long long v1, long long v2) {
	vector<int> tk1 = token(v1), tk2 = token(v2);
	int i;
	long long curr = 0ll;
	for (i = 0 ; i < 19; i++) {
		curr = curr * 10 + (tk1[i] + tk2[i]) % 10;
	}
	
	return curr;
}

long long authorityans() {
	int i, j;
	long long ans = 0ll;
	for (i = 0 ; i < (int) allnum.size(); i++) {
		for (j = i + 1; j < (int) allnum.size(); j++) {
			ans = max(addition(allnum[i], allnum[j]), ans);
		}
	}
	
	return ans;
}

int main(int argc, char *argv[]) {	
	unordered_set<long long> h;
	int n, i, j = 1;
	while (scanf("%d", &n) != EOF) {
		root = new node();
		long long ans = 0;
		for (i = 0 ; i < n; i++) {
			long long v1;
			cin >> v1;
			vector<int> took = token(v1);
			if (h.find(v1) == h.end()) {
				h.insert(v1);
				rt = 0ll;
				findans(root, took, 0);
				ans = max(ans, rt);
				root = insertion(root, took, 0);
				allnum.push_back(v1);
			}
		}
		
		if (ans != authorityans()) {
			cout << "fail the test case " << j << " expected " << authorityans() << " output " << ans << endl;
		} else {
			cout << "pass the test case " << j << endl; 
		}
		allnum.clear();
		j++;
	}
	return 0;
}


