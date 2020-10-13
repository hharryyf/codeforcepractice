#include <bits/stdc++.h>
using namespace std;
int n;
string s;
bool remove() {
    // remove a character that has one below adjacent
    // and no above adjacent
    int to_remove = -1;
    for (int i = 0; i < s.length(); i++) {
        bool has_below = (i != 0 && s[i-1] == s[i]-1) || (i+1 != s.length() && s[i+1] == s[i]-1);
        bool has_above = (i != 0 && s[i-1] == s[i]+1) || (i+1 != s.length() && s[i+1] == s[i]+1);
        if (has_below && !has_above) {
            // remove dis
            if (to_remove == -1 || s[i] > s[to_remove])
                to_remove = i;
        }
    }
    if (to_remove != -1) {    
        s.erase(to_remove, 1);
        return true;
    }
    return false;
}
int main() {
    cin >> n >> s;
    while (remove()) {}
    cout << (n-s.length()) << endl;
}