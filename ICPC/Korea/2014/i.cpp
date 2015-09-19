#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
long long data[100000][2];
const long long INF = 2000000001;

bool isValid(long long r) {
	long long minX = data[0][0], maxX = data[0][0], minY = data[0][1], maxY = data[0][1];
	for(int i = 1; i < n; i++) {
		minX = min(minX, data[i][0]);
		maxX = max(maxX, data[i][0]);
		minY = min(minY, data[i][1]);
		maxY = max(maxY, data[i][1]);
	}

	long long sx[4] = {minX, minX, maxX - r, maxX - r};
	long long sy[4] = {minY, maxY - r, minY, maxY - r};

	for(int type = 0; type < 4; type++) {
		long long minX2 = INF, maxX2 = -INF, minY2 = INF, maxY2 = -INF;
		for(int i = 0; i < n; i++) {
			long long x = data[i][0], y = data[i][1];
			if(sx[type] <= x and x <= sx[type] + r and sy[type] <= y and y <= sy[type] + r) continue;
			minX2 = min(minX2, data[i][0]);
			maxX2 = max(maxX2, data[i][0]);
			minY2 = min(minY2, data[i][1]);
			maxY2 = max(maxY2, data[i][1]);
		}

		if(minX2 == INF) return true;

		bool isOut = false;
		for(int i = 0; i < n; i++) {
			long long x = data[i][0], y = data[i][1];
			if(sx[type] <= x and x <= sx[type] + r and sy[type] <= y and y <= sy[type] + r) continue;
			if(	minX2 <= x and x <= minX2 + r and minY2 <= y and y <= minY2 + r or
				maxX2 - r <= x and x <= maxX2 and maxY2 - r <= y and y <= maxY2) continue;
			if(	minX2 <= x and x <= minX2 + r and maxY2 - r <= y and y <= maxY2 or
				maxX2 - r <= x and x <= maxX2 and minY2 <= y and y <= minY2 + r) continue;
			isOut = true;
			break;
		}
		if(!isOut) return true;
	}

	return false;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%lld %lld", data[i], data[i] + 1);
		long long s = 0, e = 2000000001, ans;
		while(s < e) {
			long long mid = (s + e) / 2;
			if(isValid(mid)) ans = e = mid;
			else s = mid + 1;
		}

		printf("%lld\n", ans);
	}

	return 0;
}
