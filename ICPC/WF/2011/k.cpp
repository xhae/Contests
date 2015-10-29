#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>

using namespace std;

const double EPS = 1e-9;
bool EQ(double a, double b) { return abs(a - b) < EPS; }

struct Point {
	double x, y, rad;
	Point operator + (Point a) { return {x + a.x, y + a.y}; }
	Point operator - (Point a) { return {x - a.x, y - a.y}; }
	bool operator == (Point a) { return EQ(x, a.x) and EQ(y, a.y); }
	Point rotate(double rad) { return {x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)}; }
	Point norm() { double sz = size(); return {x / sz, y / sz}; }
	double size() { return hypot(x, y); }
	double dist(Point a) { return (*this - a).size(); }
};
int n;

vector<Point> pts;
const double PI = acos(-1.0);

int ccw(Point a, Point b, Point c) {
	Point gap[2] = {b - a, c - a};
	double res = gap[0].x * gap[1].y - gap[1].x * gap[0].y;
	if(EQ(res, 0)) return 0;
	if(res < 0) return -1;
	return 1;
}

int main(void) {
	int kase = 0;
	while(scanf("%d", &n), n > 0) {
		pts.resize(n);
		Point base{0, 10001};
		for(int i = 0; i < n; i++) {
			scanf("%lf %lf", &pts[i].x, &pts[i].y);
			if(pts[i].y < base.y or (pts[i].y == base.y and pts[i].x > base.x))
				base = pts[i];
		}
		for(int i = 0; i < n; i++)
			if(pts[i] == base) pts[i].rad = 0;
			else pts[i].rad = atan2(pts[i].y - base.y, pts[i].x - base.x);
			sort(pts.begin(), pts.end(), [base](const Point &a, const Point &b) {
				if(!EQ(a.rad, b.rad)) return a.rad < b.rad;
				auto _a = a, _b = b;
				return _a.dist(base) < _b.dist(base); 
			});
		pts.push_back(pts[0]);

		stack<Point> st;
		st.push(pts[0]);
		st.push(pts[1]);
		st.push(pts[2]);
		
		for(int i = 3; i < pts.size(); i++) {
			Point p3 = pts[i];
			while(true) {
				Point p2 = st.top();
				st.pop();
				Point p1 = st.top();
				
				if(ccw(p1, p2, p3) > 0) {
					st.push(p2);
					st.push(p3);
					break;
				}
			}
		}
	
		vector<Point> conv;
		while(!st.empty()) {
			conv.push_back(st.top());
			st.pop();
		}

		double ans = 99999999;
		for(int i = 0; i < conv.size() - 1; i++) {
			double cand = 0;
			for(int j = 0; j < conv.size(); j++) {
				if(j == i or j == i + 1) continue;
				Point p0 = conv[i], d0 = (conv[i + 1] - conv[i]).norm(), d1 = d0.rotate(PI / 2), p1 = conv[j];
				if(EQ(d0.x, 0)) {
					swap(p0.x, p0.y);
					swap(d0.x, d0.y);
					swap(p1.x, p1.y);
					swap(d1.x, d1.y);
				}

				cand = max(cand, (p1.y - p0.y - d0.y * (p1.x - p0.x) / d0.x) / (d0.y * d1.x / d0.x - d1.y));
			}
			ans = min(ans, cand);
		}

		long long ians = ans * 100 + 1 - EPS;
		printf("Case %d: %lld.%02lld\n", ++kase, ians / 100, ians % 100);
	}

	return 0;
}
