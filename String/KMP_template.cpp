#pragma GCC optimize(3)
#include <bits/stdc++.h>

using namespace std;

vector<int> calnext(string &p) {
	vector<int> ret = vector<int>(p.length(), 0);
	ret[0] = -1;
	int plen = p.length();
	int k = -1, j = 0;
	while (j < plen - 1) {
		  if (k == -1 || p[j] == p[k]) {
		  	 j++, k++;
		  	 if (p[j] != p[k]) {
					  ret[j] = k;   
    			} else {
				ret[j] = ret[k];
			} 
		  } else {
 		  	 k = ret[k];
		  }
	}	
	
	return ret;	
}

int KMP(string &s, string &p) {
	vector<int> next = calnext(p);
	int i = 0, j = 0, slen = s.length(), plen = p.length();
	while (i < slen && j < plen) {
	    if (j == -1 || s[i] == p[j]) {
		    i++, j++;
	    } else {
		    j = next[j];
		}
	} 
	
	if (j == plen) {
	   return i - j;
	}
	
	return -1;
}
//////////////////////////////////////////////////////////////////////////////
// below sections are all testing functions
int jury(string &str1, string &str2) {
	 unsigned int idx = str1.find(str2);
	 if (idx == string::npos) return -1;
	 return idx;	 
} 

string genstring() {
	   srand(time(NULL));
	   string s = "";
	   int n = 200 + rand() % 1000;
	   while (n > 0) {
	   		 char ch = 'a' + rand() % 5;
	   		 s += ch;
	   		 n--;
	   }
	   return s;
}



void unit_test() {
	 int i;
	 for (i = 1; i <= 200; i++) {
	 	 string s = genstring();
	 	 int len = s.length();
	 	 srand(time(NULL));
         int l = rand() % len;
	 	 string p = s.substr(l);
	 	 int ot1 = KMP(s, p), ot2 = jury(s, p);
	 	 if (ot1 != ot2) {
		  	printf("------------------wrong answer on test case %d-------------------\n", i);
		  	cout << "str= " << s << endl;
		  	cout << "ptr= " << p << endl;
		  	cout << "expected " << ot2 << " output " << ot1 << endl;
		  	return;
         }
	 }
	 
	 printf("pass all 200 test cases\n");
}

int main() {
    unit_test();
    return 0;
}
