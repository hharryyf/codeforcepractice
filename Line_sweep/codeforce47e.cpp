#include <bits/stdc++.h>
#define MAX_SIZE (1 << 15)

using namespace std;

/*
	we can make the following claims:
	1. since all the projection angle is less than 45 degree,
	   the larger the angle the further the body can project
	2. for each wall, if it can block a body with a higher projection angle, 
	   a body with a lesser projection angle cannot pass it
	3. for each wall, if it cannot block a body, then all the bodies that has
	   a higher projection angle can pass it as well
	4. for every flying object, we are interested in the first wall that the 
	   following thing happens
	   v*t*cos(a) = x and v*t*sin(a) - 1/2*g*t^2 <= y 
*/

typedef struct fires {
	double angle;
	int index;
} Fire;

// all the walls, pair.first->x, pair.second->y
vector<pair<double, double> > walls;

pair<double, double> ans[MAX_SIZE];
Fire fire[MAX_SIZE];

double getmaxdist(Fire f, double V);

double gety(Fire f, double x, double V);

static bool cmp(const Fire &a, const Fire &b) {
	return (a.angle < b.angle);
}

int main(int argc, char *argv[]) {
	int n, i, j, m;
	double V;
	scanf("%d %lf", &n, &V);
	for (i = 1; i <= n; i++) {
		scanf("%lf", &fire[i].angle);
		fire[i].index = i;
	}
	
	scanf("%d", &m);
	for (i = 0 ; i < m; i++) {
		double x, y;
		scanf("%lf %lf", &x, &y);
		walls.push_back(pair<double, double>(x, y));
	}
	
	// sort the shots in angle ascending order
	sort(fire + 1, fire + n + 1, cmp);
	
	// sort the walls in x increasing order
	sort(walls.begin(), walls.end());
	
	i = 1;
	j = 0;
	while (i <= n && j < m) {
		// case when the flying object cannot reach the current wall 
		// and passed all the previous walls, it would land on the ground
		if (getmaxdist(fire[i], V) <= walls[j].first) {
			ans[fire[i].index] = pair<double, double>(getmaxdist(fire[i], V), 0.0);
			i++;
		} else {
			double y = gety(fire[i], walls[j].first, V);
			if (y <= walls[j].second) {
				// if the fire cannot pass the current wall
				ans[fire[i].index] = pair<double, double>(walls[j].first, y);
				i++;
			} else {
				// this means the current wall cannot block anything else
				j++;
			}
		}
	}
	
	// edge case, the remaining bodies can fly through all the walls
	while (i <= n) {
		ans[fire[i].index] = pair<double, double>(getmaxdist(fire[i], V), 0.0);
		i++;
	}
	
	for (i = 1; i <= n; i++) {
		printf("%lf %lf\n", ans[i].first, ans[i].second);
	}
	return 0;
}

double gety(Fire f, double x, double V) {
	double t = x / (V * cos(f.angle));
	return V * sin(f.angle) * t - 4.9 * t * t;
}

double getmaxdist(Fire f, double V) {
	return 2 * V * V * sin(f.angle) * cos(f.angle) / 9.8;
}
