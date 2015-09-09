#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

double d, loc[10], height[10];
int n, b;

const double EPS = 1e-9;
bool EQ(double a, double b) { return abs(a - b) < EPS; }

int main(void) {
	scanf("%lf %d %d", &d, &n, &b);
	for(int i = 0; i < n; i++) scanf("%lf %lf", loc + i, height + i);

	double vx = 1e15, ans = 1e15;

	for(int bounce = 0; bounce <= b; bounce++) {
		double nloc[10];
		double unit = d / (bounce + 1);
		
		bool isAble = true;
		for(int i = 0; i < n; i++) {
			nloc[i] = loc[i];
			while(nloc[i] > unit or EQ(nloc[i], unit)) nloc[i] -= unit;
			if(EQ(nloc[i], 0)) isAble = false;
		}

		if(!isAble) continue;
		
		for(int i = 0; i < n; i++) {
			double curVx = unit * nloc[i] - nloc[i] * nloc[i];
			curVx /= 2 * height[i];
			vx = min(vx, sqrt(curVx));
		}

		if(vx > sqrt(unit / 2)) ans = min(ans, sqrt(unit));
		else {
			double vy = unit / (2 * vx);
			ans = min(ans, sqrt(vx * vx + vy * vy));
		}
	}

	printf("%.10lf\n", ans);

	return 0;
}
