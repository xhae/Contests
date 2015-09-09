#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <unordered_set>

using namespace std;

bool road[52][52][4];
int mov[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const string dirs = "NESW";

vector<tuple<int, int, int, int>> dists[51][51][4][11];

int main(void) {
	int n, x0, y0, t;
	scanf("%d %d %d %d", &n, &x0, &y0, &t);
	for(int i = 0; i < n; i++) {
		int x[2], y[2];
		scanf("%d %d %d %d", x, y, x + 1, y + 1);
		if(x[0] > x[1]) swap(x[0], x[1]);
		if(y[0] > y[1]) swap(y[0], y[1]);
		if(y[0] == y[1]) {
			for(int i = x[0]; i <= x[1]; i++) {
				if(i > x[0]) road[i][y[0]][3] = true;
				if(i < x[1]) road[i][y[0]][1] = true;
			}
		} else {
			for(int i = y[0]; i <= y[1]; i++) {
				if(i > y[0]) road[x[0]][i][2] = true;
				if(i < y[1]) road[x[0]][i][0] = true;
			}
		}
	}

	for(int i = 0; i <= 50; i++)
		for(int j = 0; j <= 50; j++)
			for(int k = 0; k < 4; k++) {
				if(!road[i][j][k]) continue;

				queue<tuple<int, int, int>> curq;
				curq.push(make_tuple(i, j, k));

				for(int lv = 0; lv < 10; lv++) {
					set<tuple<int, int, int, int>> nexts;
					while(!curq.empty()) {
						int x, y, dir;
						tie(x, y, dir) = curq.front();
						curq.pop();

						if(!road[x][y][dir]) continue;

						int nx = x + mov[dir][0], ny = y + mov[dir][1];
						if(nx >= 0 and ny >= 0) {
							for(int d = -1; d <= 1; d++) {
								int ndir = (dir + d + 4) % 4;
								nexts.insert(make_tuple(nx, ny, ndir, d != 0));
							}
						}
					}
					for(auto &e: nexts) {
						int x, y, dir, turned;
						tie(x, y, dir, turned) = e;
						curq.push(make_tuple(x, y, dir));
						dists[i][j][k][lv + 1].push_back(e);
					}
				}
			}

	queue<tuple<int, int, int>> q;
	for(int i = 0; i < 4; i++) 
		if(road[x0][y0][i])
			q.push(make_tuple(x0, y0, i));

	for(int i = 0; i < t; i++) {
		int step;
		char type[2];
		scanf("%d %s", &step, type);

		set<tuple<int, int, int>> nextStart;

		while(!q.empty()) {
			int x, y, dir;
			tie(x, y, dir) = q.front();
			q.pop();

			for(auto &next: dists[x][y][dir][step]) {
				int x, y, ndir, turned;
				tie(x, y, ndir, turned) = next;
				if(turned) {
					if(dirs[ndir] == type[0]) nextStart.insert(make_tuple(x, y, ndir));
				} else {
					if(dirs[ndir] == type[0]) 
						for(int d = -1; d <= 1; d++) {
							int curDir = (ndir + d + 4) % 4;
							nextStart.insert(make_tuple(x, y, curDir));
						}
				}
			}
		}

		for(auto &e: nextStart) q.push(e);
	}

	set<tuple<int, int>> ans;
	while(!q.empty()) {
		int x, y, dir;
		tie(x, y, dir) = q.front();
		q.pop();
		if(road[x][y][dir]) ans.insert(make_tuple(x, y));
	}
	
	for(auto &e: ans) printf("%d %d\n", get<0>(e), get<1>(e));

	return 0;
}
