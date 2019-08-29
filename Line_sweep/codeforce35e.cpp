#include <bits/stdc++.h>

using namespace std;

// event = 0 or event = 1 stands for left edge/right edge
typedef struct line {
	int event;
	int x;
	int y;
} Line;

// stores the height of tallest 
map<int, int, greater<int> > s = map<int, int, greater<int> >();
// ans
vector<pair<int, int> > ans;
// all the buildings lines
vector<Line> building;

static bool cmp(const Line &l1, const Line &l2) {
	if (l1.x != l2.x) {
		return l1.x < l2.x;
	}
	
	if (l1.event != l2.event) {
		return l1.event < l2.event;
	}
	
	if (l1.event == 0) {
		return l1.y > l2.y;
	}
	
	return l1.y < l2.y;
}

int main(int argc, char *argv[]) {
	int i, n;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for (i = 0 ; i < n; i++) {
		int h, l, r;
		scanf("%d%d%d", &h, &l, &r);
		Line l1, l2;
		l1.event = 0, l1.x = l, l1.y = h;
		l2.event = 1, l2.x = r, l2.y = h;
		building.push_back(l1);
		building.push_back(l2);
	}
	
	
	sort(building.begin(), building.end(), cmp);
	s[0] = 1;
	
	for (auto bd : building) {
		// starting point
		int currentmax = s.begin()->first;
		if (bd.event == 0) {
			if (currentmax < bd.y) {
				ans.push_back(pair<int, int>(bd.x, currentmax));
				ans.push_back(pair<int, int>(bd.x, bd.y));
			}
			
			s[bd.y]++;
		} else {
		// end point
			
			
			s[bd.y]--;
			if (s[bd.y] <= 0) {
				s.erase(bd.y);
			}   
			
			currentmax = s.begin()->first;
			
			if (bd.y > currentmax) {
				ans.push_back(pair<int, int>(bd.x, bd.y));
				ans.push_back(pair<int, int>(bd.x, currentmax));
			}
		}
	}
	
	
	cout << ans.size() << endl;
	for (auto pt : ans) {
		cout << pt.first << " " << pt.second << endl;
	}
	return 0;
}
