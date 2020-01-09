#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 111
typedef long long ll;
using namespace std;

// y1 < y2
struct walls {
    double x, y1, y2;
};

struct edge {
    int x1, x2;
    double w;
};

struct pt {
    double x, y;
};

vector<pt> pts;
vector<edge> edg;
double dist[MAX_SIZE];
vector<walls> wall;

void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; i++) {
        dist[i] = 1e7;
    }
    
    pts.clear(), edg.clear(), wall.clear();
}

void addedge(int i, int j) {
    double d = sqrt((pts[i].x - pts[j].x) * (pts[i].x - pts[j].x) + (pts[i].y - pts[j].y) * (pts[i].y - pts[j].y));
    edg.push_back(edge{i, j, d});
    edg.push_back(edge{j, i, d});
}

bool cross(pt a, pt b, walls w) {
    if (a.x == b.x) return false;
    if (a.x > b.x) swap(a, b);
    double k = (b.y - a.y) / (b.x - a.x);
    double bb = a.y - k * a.x;
    double yc = w.x * k + bb;
    return (yc > w.y1) && (yc < w.y2) && (a.x < w.x) && (w.x < b.x);
}

double bellmanford() {
    dist[0] = 0.0;
    int i;
    for (i = 0 ; i < pts.size(); i++) {
        for (auto e : edg) {
            dist[e.x2] = min(dist[e.x2], dist[e.x1] + e.w);
        }
    }
    return dist[pts.size() - 1];
}

int main() {
    int n, i, j;
    while (scanf("%d", &n) != EOF) {
        if (n == -1) break;
        
        init();
        
        pts.push_back(pt{0.0, 5.0});
        
        for (i = 0 ; i < n; i++) {
            double x, y1, y2, y3, y4;
            scanf("%lf%lf%lf%lf%lf", &x, &y1, &y2, &y3, &y4);
            wall.push_back(walls{x, 0.0, y1});
            wall.push_back(walls{x, y2, y3});
            wall.push_back(walls{x, y4, 10.0});
            pts.push_back(pt{x, y1});
            pts.push_back(pt{x, y2});
            pts.push_back(pt{x, y3});
            pts.push_back(pt{x, y4});
        }
        pts.push_back(pt{10.0, 5.0});
    
        for (i = 0 ; i < pts.size(); i++) {
            for (j = i + 1 ; j < pts.size(); j++) {
                bool valid = true;
                for (auto wa : wall) {
                    if (cross(pts[i], pts[j], wa)) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    addedge(i, j);
                }
            }
        }
        
        printf("%.2lf\n", bellmanford());
    }
	return 0;
}
