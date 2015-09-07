#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const double EPS = 1e-9;
bool EQ(double a, double b) { return abs(a - b) < EPS; }

struct Point {
	double x, y;
	Point operator + (const Point a) const { return Point{x + a.x, y + a.y}; }
	Point operator - (const Point a) const { return Point{x - a.x, y - a.y}; }
	Point operator * (const double a) const { return Point{x * a, y * a}; }
	Point rotate(double rad) { return Point{x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)}; }
	double sz() { return hypot(x, y); }
	Point norm() { double s = sz(); return Point{x / s, y / s}; }
	bool operator == (const Point &a) const { return EQ(x, a.x) and EQ(y, a.y); }
} pts[100];
int n;

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%lf %lf", &pts[i].x, &pts[i].y);
		int d;
		double p;
		scanf("%d %lf", &d, &p);
		
		Point cur = pts[0];
		double incRatio;
		double rotateRad = 0;
		double totSize = 0;
		for(int i = 0; i < n - 1; i++) totSize += (pts[i + 1] - pts[i]).sz();
		incRatio = totSize / (pts[n - 1] - pts[0]).sz();

		double ratio = 1;
		for(int lv = 0; lv < d; lv++) {
//			printf("(%.10lf, %.10lf), %lf\n", cur.x, cur.y, ratio);
			for(int i = 0; i < n - 1; i++) {
				double curP = (pts[i + 1] - pts[i]).sz() / totSize;
//				printf("%lf %lf\n", p, curP);
				if(curP > p) {
					if(lv == d - 1) {
						double toGoRatio = p / curP;
//						printf("togo: %lf %lf, %lf\n", toGoRatio, rotateRad, (pts[i + 1] - pts[i]).sz());
						cur = cur + (pts[i + 1] - pts[i]).rotate(rotateRad) * ratio * toGoRatio;
					} else {
						Point curDir = (pts[i + 1] - pts[i]).norm().rotate(rotateRad);
						Point sDir = (pts[n - 1] - pts[0]).norm();
						double rad = acos(curDir.x * sDir.x + curDir.y * sDir.y);
						if(sDir.rotate(rad) == curDir) rotateRad = rad;
						else rotateRad = -rad;

						ratio *= curP * incRatio;
						p = p / curP;
					}
					break;
				}

				p -= curP;
				cur = cur + (pts[i + 1] - pts[i]).rotate(rotateRad) * ratio;
//				printf("loc: %lf %lf, %lf %lf\n", cur.x, cur.y, ((pts[i + 1] - pts[i]) * ratio).sz(), ratio);
			}
		}

		printf("(%.10lf, %.10lf)\n", cur.x, cur.y);
	}

	return 0;
}
