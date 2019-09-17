#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define MAX_SIZE (2000000 + 11)
using namespace std;

char a[MAX_SIZE], b[MAX_SIZE];

bool matching(char s[], char t[]);

int main(int argc, char *argv[]) {
	while (scanf("%s%s", a, b) != EOF) {
		if (matching(a, b)) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
	return 0;
}

bool matching(char s[], char t[]) {
	int i = 0, j = 0, n = strlen(s), m = strlen(t);
	while (i < n && j < m) {
		if (s[i] == t[j]) {
			i++;
			j++;
		} else {
			j++;
		}
	}
	
	return (i == n);
}
