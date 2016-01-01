#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

struct Point {
	double x, y;
	Point operator + (Point &a) { return Point{x + a.x, y + a.y}; }
	Point operator - (Point &a) { return Point{x - a.x, y - a.y}; }
	Point operator * (double a) { return Point{x * a, y * a}; }
	double size() { return hypot(y, x); }
	double dist(Point &a) { return (*this - a).size(); }
	Point norm() { double sz = size(); return Point{x / sz, y / sz}; }
	Point rotate(double rad) { return Point{x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)}; }
};

const double EPS = 1e-9;
const bool EQ(double a, double b) {
	if(abs(a - b) < EPS) return true;
	if(abs(b) > EPS and abs(a / b - 1) < EPS) return true;
	return false;
}

int n;
Point pts[5000];
int group[5000], groupsize[5000], gn;
int tried[5000], trycnt;

int main(void) {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%lf %lf", &pts[i].x, &pts[i].y);

	memset(group, -1, sizeof(group));
	for(int i = 0; i < n; i++)
		if(group[i] == -1) {
			group[i] = gn;
			queue<int> q;
			q.push(i);
			int cursize = 0;
//			printf("%d\n", gn);
			while(!q.empty()) {
				int cur = q.front();
				q.pop();
				cursize++;

//				printf("\t%d\n", cur);

				for(int j = 0; j < n; j++)
					if(group[j] == -1) {
						double dist = pts[cur].dist(pts[j]);
//						printf("%lf %lf, %lf %lf, %lf\n", pts[cur].x, pts[cur].y, pts[j].x, pts[j].y, dist);
						if(dist < 2 or EQ(dist, 2)) {
							group[j] = gn;
							q.push(j);
						}
					}
			}

			groupsize[gn++] = cursize;
		}

	int ans = 0;
	for(int i = 0; i < gn; i++) ans = max(ans, groupsize[i] + 1);

	long long cnt = 0;
	for(int i = 0; i < n; i++) {
		vector<Point> dirs;
		for(int j = i + 1; j < n; j++) {
			if(group[i] == group[j]) continue;
			double dist = pts[i].dist(pts[j]);
			if(EQ(dist, 4)) dirs.push_back(pts[j] - pts[i]);
			else if(dist < 4) {
				double width = pts[i].dist(pts[j]) / 2;
				double rad = acos(width / 2);
				dirs.push_back((pts[j] - pts[i]).rotate(rad));
				dirs.push_back((pts[j] - pts[i]).rotate(-rad));
			}
		}

		for(auto &dir: dirs) {
			trycnt++;
			dir = dir.norm();
			dir = dir * 2;
			Point center = pts[i] + dir;

			int curans = 1;
			for(int j = 0; j < n; j++) {
				double dist = center.dist(pts[j]);
				if(dist < 2 or EQ(dist, 2)) {
					if(tried[group[j]] != trycnt) {
						tried[group[j]] = trycnt;
						curans += groupsize[group[j]];
					}
				}
			}

			ans = max(ans, curans);
//			printf("curans: %d %d\n", curans, ans);
//
			cnt += n;
		}

		if(cnt > 50000000) break;
	}

	printf("%d\n", ans);

	return 0;
}
