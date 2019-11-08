/*
	source 
	https://github.com/morris821028/UVa/blob/master/temp/UVaDate/12647%20-%20Balloon%5Bv3%5D.cpp
*/

#include <bits/stdc++.h>
#define eps 1e-6
using namespace std;

const int MAXN = 131072;

// points, sorted by x in increasing order then by y in increasing order
struct Pt {
    int x, y, label;
    Pt(int a = 0, int b = 0, int c = 0):
    	x(a), y(b), label(c) {}
    bool operator<(const Pt &a) const {
        if(x != a.x)	return x < a.x;
        return y < a.y;
    }
    // manhattan distance of a point
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
};

// segment, the invariant is e > s
// c refers to the event type
struct Seg {
	Pt s, e;
	int id;
	Seg(Pt a = Pt(), Pt b = Pt(), int c = 0):
		s(a), e(b), id(c) {}
};

// end point of the segment, x coordinate, event type I, segment id, event type II
struct Endpoint {
	int x, s, id, qkind;
	Endpoint(int a = 0, int b = 0, int c = 0, int d = 0):
		x(a), s(b), id(c), qkind(d) {}
	// sort according to x first and event type I bext and then event type II 
	bool operator<(const Endpoint &a) const {
		if (x != a.x)	return x < a.x;
		if (s != a.s)	return s > a.s;
		return qkind < a.qkind;
	}
};

// invariant, x is strictly increasing, no segments intersect
struct CMP {
	// the current sweeping line, x coordinate is
	static int x;
	// interpolate works as follows, give 2 endpoints
	// find the y coordinate of the current static int 'x'
	// smaller x dominates larger x
	double interpolate(const Pt& p1, const Pt& p2, int& x) {
        if (p1.x == p2.x) return p1.y;
        return p1.y + (double)(p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x);
    }
    
	bool operator() (const Seg &i, const Seg &j) {
		return interpolate(i.s, i.e, x) < interpolate(j.s, j.e, x);
	}
};
int CMP::x = 0;
set<Seg, CMP>::iterator prevNode(set<Seg, CMP>::iterator it, set<Seg, CMP>& S) {
	return it == S.begin() ? it : --it;
}
set<Seg, CMP>::iterator nextNode(set<Seg, CMP>::iterator it, set<Seg, CMP>& S) {
	return it == S.end() ? it : ++it;
}
// towards is the uppermost parent of a segment
// stopX, the x coordinate which the balloon is stopped
// stopY, the y coordinate which the balloon is stopped
int toward[MAXN], stopX[MAXN], stopY[MAXN];

int touch[MAXN];
void solve(vector<Seg> segs, int Qx[], int Q) {
	int N = segs.size();
	for (int i = 0; i < N; i++) {
		// the parent, stopX initialized as -1
		toward[i] = stopX[i] = -1;
		if (segs[i].e < segs[i].s)
			swap(segs[i].s, segs[i].e);
		// case when it is a horizontal bar
		// set parent to itself, stopy set to segment's y
		if (segs[i].s.y == segs[i].e.y)
			toward[i] = i, stopY[i] = segs[i].s.y;
		// case when it has gradient < 0, highY decide stopX
		else if (segs[i].s.y > segs[i].e.y)
			stopX[i] = segs[i].s.x, stopY[i] = segs[i].s.y;
		// case when the gradient is > 0, highY decide stopX
		else
			stopX[i] = segs[i].e.x, stopY[i] = segs[i].e.y;
	}
	
	vector<Endpoint> e;
	set<Seg, CMP> S;
		
	for (int i = 0; i < Q; i++) {
		// push in the query points, insertion query, kind2
		e.push_back(Endpoint(Qx[i], 1, i, 2));
		touch[i] = -1;
	}
	// insert all the segment's endpoints x coordinate
	for (int i = 0; i < N; i++) {
		int qs = segs[i].s.y > segs[i].e.y;
		int qe = segs[i].s.y < segs[i].e.y;
		// qs, qe measures whether this x point is a dominate point 1 yes, 0 no
		// insertion event 1
		e.push_back(Endpoint(segs[i].s.x, 1, i, qs));
		// deletion event -1
		e.push_back(Endpoint(segs[i].e.x, -1, i, qe));
	}
	sort(e.begin(), e.end());
	
	set<Seg, CMP>::iterator it, jt, kt;
	for (int i = 0; i < (int) e.size(); i++) {
		// x is in non-decreasing order at this point!
		CMP::x = e[i].x;
		if (e[i].qkind == 2) {
			it = S.begin();
			// touch means the segment a query point would reach
			if (it != S.end())	
				touch[e[i].id] = it->id;
			continue;
		}
		// large y
		if (e[i].qkind == 1) {
			it = S.lower_bound(segs[e[i].id]);
			jt = prevNode(it, S);
			kt = nextNode(it, S);
			if (it != S.end() && it->id != e[i].id)
				toward[e[i].id] = it->id;
			else if (kt != S.end() && kt->id != e[i].id)
				toward[e[i].id] = kt->id;
		}
		// insertion event
		if (e[i].s == 1) {
			S.insert(segs[e[i].id]);
		} else {
			it = S.lower_bound(segs[e[i].id]);
			if(it != S.end())	S.erase(it);
		}
	}
	
	//
	vector< pair<int, int> > TQ;
	for (int i = 0; i < N; i++) {
		TQ.push_back(make_pair(stopY[i], i));
	} 
	sort(TQ.begin(), TQ.end());
	// merge the segments to upper y
	for (int j = N-1; j >= 0; j--) {
		int i = TQ[j].second;
		// has upper segments
		if (toward[i] != -1) {
			if (toward[toward[i]] != toward[i])
				stopX[i] = stopX[toward[i]];
			stopY[i] = stopY[toward[i]];
			toward[i] = toward[toward[i]];
		}
	}
	// this part is very easy to understand just queries
	for (int i = 0; i < Q; i++) {
		if (touch[i] == -1)
			printf("%d\n", Qx[i]);
		else {
			int u = touch[i];
			if (toward[u] == -1)
				printf("%d\n", stopX[u]);
			else if (toward[u] == u)
				printf("%d %d\n", Qx[i], stopY[u]);
			else 
				printf("%d %d\n", stopX[u], stopY[u]);
		}
	}
}
int main() {
	int N, C, Qx[MAXN];
	while (scanf("%d %d", &N, &C) == 2) {
		vector<Seg> segs;
		for (int i = 0; i < N; i++) {
			int x1, x2, y1, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			segs.push_back(Seg(Pt(x1, y1), Pt(x2, y2), i));
		}
		
		for (int i = 0; i < C; i++)
			scanf("%d", &Qx[i]);
			
		solve(segs, Qx, C);
	}
	return 0;
}
