#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-9;

struct Point {
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
};

typedef Point Vector;

int sgn(double d1, double d2) {
	if (fabs(d1 - d2) <= eps) return 0;
	if (d1 > d2) return 1;
	return -1;
}

int dcmp(double x) {
	if (fabs(x) <= eps) return 0;
	if (x > 0) return 1;
	return -1;
}

Vector operator + (Vector A,Vector B) {
	return Vector(A.x+B.x,A.y+B.y);
}

Vector operator - (Vector A,Vector B) {
	return Vector(A.x-B.x,A.y-B.y);
}

bool operator == (const Vector A, const Vector B) {
    return dcmp(A.x-B.x) == 0 && dcmp(A.y-B.y) == 0;
}

double Dot(Vector A,Vector B) {
	return A.x*B.x+A.y*B.y;
}  

double Length(Vector A) {
	return sqrt(Dot(A,A));
}         

double Cross(Vector A,Vector B) {
	return A.x*B.y-B.x*A.y;
}
// shortest distance from p to segment(A, B)
double DistanceToSegment(Point P,Point A,Point B){
    if(A == B) {
		return Length(P-A);
	}
	
    Vector v1=B-A,v2=P-A,v3=P-B;
    
	if(dcmp(Dot(v1,v2))<0) {
		return Length(v2);
	} else if(dcmp(Dot(v1,v3))>0) {
		return Length(v3);
	} 
	
    return fabs(Cross(v1,v2)) / Length(v1);                   
}

double dist(double x1, double y1, double x2, double y2, double r) {
	Point o = Point(0, 0), p1 = Point(x1, y1), p2 = Point(x2, y2);
	double d1 = DistanceToSegment(o, p1, p2), d2, d3;
	// simple case, the line between point 1 and point 2 would not go inside the
	// circle with radius r
	if (sgn(d1, r) >= 0) {
		return Length(p2-p1);
	}
	
	d1 = Length(o-p1), d2 = Length(o-p2), d3 = Length(p1-p2);
	double theta1 = acos(r / d1), theta2 = acos(r / d2);
	double theta3 = acos((d1 * d1 + d2 * d2 - d3 * d3) / (d1 * d2 * 2.0));
	theta3 = theta3 - theta1 - theta2;
	return d1 * sin(theta1) + d2 * sin(theta2) + r * theta3;
}


int main() {
	// (x, y, v) of Persephone
	double xp, yp, vp;
	// initial pos of the ship(x, y, v) and dangerous zone radius
	double x, y, v, r;
	scanf("%lf%lf%lf%lf%lf%lf%lf", &xp, &yp, &vp, &x, &y, &v, &r);
	double low = 0.0, high = 1e7, ans = 1e7;
	// the initial theta
	double theta = atan2(yp, xp);
	// the radius of Persephone
	double R = sqrt(xp * xp + yp * yp);
	// the angular speed
	double omega = vp / R;
	int i;
	for (i = 0 ; i < 70; ++i) {
		double mid = 0.5 * (low + high);
		// angle after moving for mid seconds
		double alpha = omega * mid + theta;
		// the position when moving for mid seconds
		double tx = R * cos(alpha), ty = R * sin(alpha);
		// then we should calculate the minimum distance from (tx, ty) to (x, y)
		double d = dist(tx, ty, x, y, r);
		// cout << d << endl;
		if (sgn(v * mid, d) >= 0) {
			ans = mid;
			high = mid;
		} else {
			low = mid;
		}
	}
	printf("%.9lf\n", ans);
	return 0;
}