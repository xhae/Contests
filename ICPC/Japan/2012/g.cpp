#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

struct Point {
	double x, y, z;
	Point operator - (Point a) { return Point{x - a.x, y - a.y, z - a.z}; }
} balloons[2000], stars[15], pos;

int n, m, limit;
double radius[2000], brightness[15];
vector<int> toEliminate[15];

const double EPS = 1e-9;
bool EQ(double a, double b) { return abs(a - b) < EPS; }

int checked[2000];

int main(void) {
	int curtry = 0;
	while(scanf("%d %d %d", &n, &m, &limit), n > 0) {
		for(int i = 0; i < n; i++) scanf("%lf %lf %lf %lf", &balloons[i].x, &balloons[i].y, &balloons[i].z, radius + i);
		for(int i = 0; i < m; i++) scanf("%lf %lf %lf %lf", &stars[i].x, &stars[i].y, &stars[i].z, brightness + i);
		scanf("%lf %lf %lf", &pos.x, &pos.y, &pos.z);

		for(int i = 0; i < m; i++) {
			Point gap = stars[i] - pos;
			brightness[i] /= gap.x * gap.x + gap.y * gap.y + gap.z * gap.z;
		}

		for(int i = 0; i < m; i++) {
			toEliminate[i].clear();
			for(int j = 0; j < n; j++) {
				Point dir = stars[i] - pos;
				double p = pos.x - balloons[j].x, q = pos.y - balloons[j].y, r = pos.z - balloons[j].z;
				double rad = radius[j];

				double a = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
				double b = 2 * (p * dir.x + q * dir.y + r * dir.z);
				double c = p * p + q * q + r * r - rad * rad;
				double D = b * b - 4 * a * c;
				if(D >= 0) {
					double cand = (-b + sqrt(D)) / 2 / a;
					if(EQ(cand, 0)) cand = 0;
					if(EQ(cand, 1)) cand = 1;
					if(cand >= 0 and cand <= 1) toEliminate[i].push_back(j);
					else {
						cand = (-b - sqrt(D)) / 2 / a;
						if(EQ(cand, 0)) cand = 0;
						if(EQ(cand, 1)) cand = 1;
						if(cand >= 0 and cand <= 1) toEliminate[i].push_back(j);
					}
				}
			}
		}

		double ans = 0;
		for(int cands = 1; cands < (1 << m); cands++) {
			double curAns = 0;
			curtry++;
			for(int i = 0; i < m; i++)
				if(cands & (1 << i)) {
					curAns += brightness[i];
					for(int tar: toEliminate[i])
						checked[tar] = curtry;
				}
			
			int cnt = 0;
			for(int i = 0; i < n; i++) if(checked[i] == curtry) cnt++;
			if(cnt <= limit) ans = max(ans, curAns);
		}

		printf("%.20lf\n", ans);
	}

	return 0;
}
