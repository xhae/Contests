#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
	double x, y;
	Point operator + (const Point &a) { return Point{x + a.x, y + a.y}; }
	Point operator - (const Point &a) { return Point{x - a.x, y - a.y}; }
	Point operator * (double a) { return Point{x * a, y * a}; }
	double size() { return hypot(x, y); }
} pts[2];
double r;

const double PI = acos(-1.0);

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%lf %lf %lf %lf %lf", &pts[0].x, &pts[0].y, &pts[1].x, &pts[1].y, &r);
		double s = 0, e = 1;
		for(int lv = 0; lv < 100; lv++) {
			double m1 = (s * 2 + e) / 3;
			double m2 = (s + e * 2) / 3;

			auto dir = pts[1] - pts[0];
			Point p1 = pts[0] + dir * m1;
			Point p2 = pts[0] + dir * m2;

			double dist1 = p1.size();
			double dist2 = p2.size();

			if(dist1 > dist2) s = m1;
			else e = m2;
		}

		double closest = (pts[0] + (pts[1] - pts[0]) * s).size();
		if(closest >= r) printf("%.3lf\n", (pts[1] - pts[0]).size());
		else {
			double theta[2] = {acos(r / pts[0].size()), acos(r / pts[1].size())};
			vector<double> cands[2];
			for(int i = 0; i < 2; i++) {
				auto normRad = [](double arg) {
					while(arg >= 2 * PI) arg -= 2 * PI;
					while(arg < 0) arg += 2 * PI;
					return arg;
				};
				double base = normRad(atan2(pts[i].y, pts[i].x));
				cands[i].push_back(normRad(base - theta[i]));
				cands[i].push_back(normRad(base + theta[i]));
			}

			double minCand = 2 * PI;
			for(double c1: cands[0])
				for(double c2: cands[1]) {
					double cur = max(c1, c2) - min(c1, c2);
					cur = min(cur, 2 * PI - cur);
					minCand = min(minCand, cur);
				}

			double ans = minCand * r;
			ans += sqrt(pts[0].size() * pts[0].size() - r * r);
			ans += sqrt(pts[1].size() * pts[1].size() - r * r);
			printf("%.3lf\n", ans);
		}
	}

	return 0;
}
