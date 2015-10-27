#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

struct Point {
	int x, y;
	bool operator == (Point a) { return x == a.x and y == a.y; }
	bool operator != (Point a) { return !(*this == a); }
} data[2][500];
int n, m;

int ysum[3001], xsum[3001];
bool haveY[3001], haveX[3001];

int main(void) {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d %d", &data[0][i].x, &data[0][i].y);
	scanf("%d", &m);
	for(int i = 0; i < m; i++) scanf("%d %d", &data[1][i].x, &data[1][i].y);
	if(n != m) { printf("no\n"); return 0; }

	for(int type = 0; type < 2; type++) {
		int minx = 3001, miny = 3001;
		memset(ysum, 0, sizeof(ysum));
		memset(xsum, 0, sizeof(xsum));
		memset(haveY, 0, sizeof(haveY));
		memset(haveX, 0, sizeof(haveX));

		for(int i = 0; i < n; i++) {
			int ni = (i + 1) % n;
			if(data[type][i].x == data[type][ni].x)
				haveY[data[type][i].y] = true;
			else haveX[data[type][i].x] = true;
			minx = min(minx, data[type][i].x);
			miny = min(miny, data[type][i].y);
		}

		for(int i = 0; i <= 3000; i++) {
			ysum[i] = !haveY[i];
			xsum[i] = !haveX[i];
			if(i > 0) {
				ysum[i] += ysum[i - 1];
				xsum[i] += xsum[i - 1];
			}
		}

		for(int i = 0; i < n; i++) {
			if(data[type][i].x > 0) data[type][i].x -= xsum[data[type][i].x - 1];
			data[type][i].x -= minx;
			if(data[type][i].y > 0) data[type][i].y -= ysum[data[type][i].y - 1];
			data[type][i].y -= miny;
		}
	}

	int len = n / 2 - 1;
	bool isSame = false;
	for(int cnt = 0; cnt < 4; cnt++) {
		int start = -1;
		for(int i = 0; i < n; i++)
			if(data[0][i] == data[1][0]) {
				start = i;
				break;
			}
		if(start != -1) {
			bool curSame = true;
			for(int i = 0; i < n; i++)
				if(data[0][(i + start) % n] != data[1][i]) {
					curSame = false;
					break;
				}
			if(curSame) {
				isSame = true;
				break;
			}
		}
		for(int i = 0; i < n; i++) {
			Point cur = data[0][i];
			Point ncur{len - cur.y, cur.x};
			data[0][i] = ncur;
		}
	}

	printf("%s\n", isSame ? "yes" : "no");
	return 0;
}
