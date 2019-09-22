#include <bits/stdc++.h>

using namespace std;

char s[201];

vector<string> splits(char st[], string special) {
	vector<string> ret;
	unordered_set<char> spc;
	for (auto sp : special) {
		spc.insert(sp);
	}
	string tmp = "";
	for (int i = 0 ; i < (int) strlen(st); i++) {
		if (spc.find(st[i]) !=  spc.end()) {
			if (tmp.length() != 0) {
				ret.push_back(tmp);
			}
			
			tmp = "";
		} else {
			tmp += st[i];
		}
	}
	
	if (tmp.length() != 0) {
		ret.push_back(tmp);
	}
	
	return ret;
}



int main() {
	int n, i = 0;
	scanf("%d", &n);
	getchar();
	while(i < n) {
		fgets(s, 201, stdin);
		cout << "we get the string " << s << "after split is " << endl;
		vector<string> r = splits(s, " \n");
		for (auto rt : r) {
			cout << rt << endl;
		}
		i++;
	}
	int v1, v2;
	scanf("%d%d", &v1, &v2);
	cout << v1 << " " << v2 << endl;
	return 0;
}
