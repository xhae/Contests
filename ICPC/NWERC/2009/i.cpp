#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const double EPS = 1e-9;
bool EQ(double a, double b) { return abs(a - b) < EPS; }

struct Point {
	double x, y, rad, dist;
	int ind;
	bool operator < (const Point &a) const {
		if(!EQ(rad, a.rad)) return rad < a.rad;
		return dist < a.dist;
	}
} pts[2000];
int n;

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		Point base{0, 10001, 0};
		for(int i = 0; i < n; i++) {
			scanf("%lf %lf", &pts[i].x, &pts[i].y);
			pts[i].ind = i;
			if(pts[i].y < base.y or (pts[i].y == base.y and pts[i].x > base.x)) base = pts[i];
		}

		for(int i = 0; i < n; i++) {
			pts[i].rad = atan2(pts[i].y - base.y, pts[i].x - base.x);
			if(pts[i].rad < 0) pts[i].rad += 2 * acos(-1.0);
			pts[i].dist = hypot(pts[i].x - base.x, pts[i].y - base.y);
		}
		sort(pts, pts + n);
		int ind = n - 1;
		while(ind >= 0 and EQ(pts[ind].rad, pts[n - 1].rad)) {
			pts[ind].dist *= -1;
			ind--;
		}
		sort(pts, pts + n);
		for(int i = 0; i < n; i++) printf("%d ", pts[i].ind);
		printf("\n");
	}

	return 0;
}
