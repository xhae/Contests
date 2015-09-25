#include <cmath>
#include <algorithm>
#include <cstdio>
#include <tuple>
#include <vector>
#include <set>

using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);
const double INF = 1e3;
bool EQ(double a, double b) { return abs(a - b) < EPS; }

struct Point {
	double x, y;
	Point operator + (Point a) { return Point{x + a.x, y + a.y}; }
	Point operator - (Point a) { return Point{x - a.x, y - a.y}; }
	Point operator * (double a) { return Point{x * a, y * a}; }
	double operator * (Point a) { return x * a.y - y * a.x; }
	Point operator / (double a) { return Point{x / a, y / a}; }

	bool operator == (const Point a) const { return EQ(x, a.x) && EQ(y, a.y); }
	bool operator != (const Point a) const { return !(*this == a); }
	bool operator < (const Point a) const {
		if(!EQ(x, a.x)) return x < a.x;
		if(EQ(y, a.y)) return false;
		return y < a.y;
	}
	bool operator > (const Point a) const { return a < (*this); }

	Point norm() { double d = hypot(x, y); return Point{x / d, y / d}; }
	double size() { return hypot(x, y); }
	Point rotate(double rad) { 
		return Point{x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)}; 
	}
	Point reflect(Point p1, Point p2) {
		Point originRoot = p2 - p1;
		double rad = atan2(originRoot.y, originRoot.x);
		if(rad < 0) rad += 2 * PI;
		rad *= 2;

		Point tar = (*this) - p1;

		Point ret = {tar.x * cos(rad) + tar.y * sin(rad), 
			tar.x * sin(rad) - tar.y * cos(rad)};
		ret = ret + p1;

		return ret;
	}

	void print() const { printf("(%.2lf %.2lf) ", x, y); }
};

double ccw(Point a, Point b, Point c) // ab to ac
{
	double gap[2][2] = {{b.x - a.x, c.x - a.x}, {b.y - a.y, c.y - a.y}};
	double ret = gap[0][0] * gap[1][1] - gap[0][1] * gap[1][0];
	if(EQ(ret, 0)) ret = 0;
	return ret;
}

struct Segment
{
	Point from, to;

	bool covers(Point tar)
	{
		if(tar == from) return true;

		Point dv = to - from;
		Point dv2 = tar - from;

		return (dv.size() > dv2.size() || EQ(dv.size(), dv2.size())) &&
			(dv.norm() == dv2.norm());
	}

	bool isCross(Segment tar, bool orTouch = true)
	{
		double product[4] = {ccw(from, to, tar.from), ccw(from, to, tar.to),
			ccw(tar.from, tar.to, from), ccw(tar.from, tar.to, to)};

		if(orTouch)
		{
			if(product[0] * product[1] <= 0 && product[2] * product[3] <= 0)
			{
				if(product[0] == 0 && product[1] == 0)
					return covers(tar.from) || covers(tar.to) || 
						tar.covers(from) || tar.covers(to);
				return true;
			}
		}
		else
		{
			if(product[0] * product[1] < 0 && product[2] * product[3] < 0) return true;
		}

		return false;
	}

	tuple<int, Point> getCross(Segment tar)	// 0 for valid, 1 for non-cross point, 2 for much cross points
	{
		if(isCross(tar) == false) return make_tuple(1, Point{0, 0});

		Point p1 = from, p2 = to, p3 = tar.from, p4 = tar.to;
		if(p1 > p2) swap(p1, p2);
		if(p3 > p4) swap(p3, p4);

		Segment s1 = *this, s2 = tar;
		if(p1 > p3) { swap(s1, s2); swap(p1, p3); swap(p2, p4); }

		bool isMuch = false;
		if((s1.covers(p3) && s1.covers(p4)) || (s2.covers(p1) && s2.covers(p2))) 
			isMuch = true;
		if(s1.covers(p3) && s2.covers(p2) && p2 != p3) isMuch = true;

		if(isMuch) return make_tuple(2, Point{0, 0});

		if(p2 == p3) return make_tuple(0, p2);

		Point dv = p2 - p1, dv2 = p4 - p3;
		double t = (p3 - p1) * dv2 / (dv * dv2);
		//		double s = (p1 - p3) * dv / (dv2 * dv);

		return make_tuple(0, p1 + dv * t);
	}

	double dist(Point a)
	{
		double ret = min((from - a).size(), (to - a).size());
		Point orth = (to - from).rotate(PI / 2).norm() * ret;

		int flag;
		Point intersect;
		tie(flag, intersect) = getCross(Segment{a - orth, a + orth});

		if(flag == 0) ret = (intersect - a).size();

		return ret;
	}

	vector<Point> crossCircle(Point center, double r) {
		if(from == to) {
			if(EQ((from - center).size(), r)) return vector<Point>{from};
			return vector<Point>();
		}

		double A1 = from.x - to.x;
		double B1 = to.x - center.x;
		double A2 = from.y - to.y;
		double B2 = to.y - center.y;
		double a = A1 * A1 + A2 * A2;
		double b = 2 * (A1 * B2 + A2 * B2);
		double c = B1 * B1 + B2 * B2 - r * r;
		double d = b * b - 4 * a * c;
		vector<Point> ret;
		if(!EQ(d, 0) && d < 0) return ret;
		double t1 = (-b + sqrt(d)) / 2 / a;
		double t2 = (-b - sqrt(d)) / 2 / a;
		if(EQ(t1, 0) || EQ(t1, 1) || (0 < t1 && t1 < 1)) ret.push_back(from * t1 + to * (1 - t1));
		if(!EQ(t1, t2) && (EQ(t2, 0) || EQ(t2, 1) || (0 < t2 && t2 < 1))) ret.push_back(from * t2 + to * (1 - t2));
		return ret;
	}
};

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		Point pt;
		scanf("%d %lf %lf", &n, &pt.x, &pt.y);
		vector<int> ans;
		while(n--) {
			int m;
			scanf("%d", &m);
			vector<Point> pts(m);
			for(int i = 0; i < m; i++) scanf("%lf %lf", &pts[i].x, &pts[i].y);

			bool bound = false;
			for(int i = 0; i < m; i++) {
				Segment seg{pts[i], pts[(i + 1) % m]};
				if(seg.covers(pt)) bound = true;
			}
			if(bound) {
				ans.push_back(0);
				continue;
			}

			in

	}

	return 0;
}
