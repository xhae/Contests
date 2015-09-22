#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

int n, data[1000][3];
int dir[1000];

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%d %d %d", data[i], data[i] + 1, data[i] + 2);
	
		fill(dir, dir + n, -1);
		dir[0] = 0;

		queue<int> q;
		q.push(0);
		while(!q.empty()) {
			int cur = q.front();
			q.pop();
			for(int i = 0; i < n; i++) {
				if(dir[i] >= 0) continue;
				int rsum = data[cur][2] + data[i][2];
				int gx = data[cur][0] - data[i][0];
				int gy = data[cur][1] - data[i][1];
				if(gx * gx + gy * gy == rsum * rsum) {
					dir[i] = !dir[cur];
					q.push(i);
				}
			}
		}

		for(int i = 0; i < n; i++) {
			if(dir[i] == -1) {
				printf("not moving\n");
				continue;
			}
			int gcdv = __gcd(data[0][2], data[i][2]);
			int a = data[0][2] / gcdv, b = data[i][2] / gcdv;
			if(b == 1) printf("%d ", a);
			else printf("%d/%d ", a, b);
			printf("%s\n", dir[i] == 0 ? "clockwise" : "counterclockwise");
		}
	}

	return 0;
}
