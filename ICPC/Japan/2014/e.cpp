#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <queue>

using namespace std;

bool road[52][52];
int mov[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const string dirs = "NESW";

int main(void) {
	int n, x0, y0, t;
	scanf("%d %d %d %d", &n, &x0, &y0, &t);
	for(int i = 0; i < n; i++) {
		int x[2], y[2];
		scanf("%d %d %d %d", x, y, x + 1, y + 1);
		if(x[0] > x[1]) swap(x[0], x[1]);
		if(y[0] > y[1]) swap(y[0], y[1]);
		for(int cy = y[0]; cy <= y[1]; cy++)
			for(int cx = x[0]; cx <= x[1]; cx++)
				road[cx][cy] = true;
	}

	queue<tuple<int, int, int>> q;
	for(int i = 0; i < 4; i++) q.push(make_tuple(x0, y0, i));
	for(int i = 0; i < t; i++) {
		int step;
		char type[2];
		scanf("%d %s", &step, type);

		bool isVisited[52][52][4] = {false, };

		set<tuple<int, int, int>> nextStart;

		while(!q.empty()) {
			queue<tuple<int, int, int>> curq;
			curq.push(q.front());
			q.pop();

			for(int j = 0; j < step; j++) {
				set<tuple<int, int, int>> nexts;
				while(!curq.empty()) {
					int x, y, dir;
					tie(x, y, dir) = curq.front();
					curq.pop();

					int nx = x + mov[dir][0], ny = y + mov[dir][1];
					if(nx >= 0 and ny >= 0 and road[nx][ny]) {
						for(int d = -1; d <= 1; d++) {
							int ndir = (dir + d + 4) % 4;
							if(nexts.count(make_tuple(nx, ny, ndir)) == 0) nexts.insert(make_tuple(nx, ny, ndir));
							if(j == step - 1) {
								if(dirs[dir] == type[0]) nextStart.insert(make_tuple(nx ,ny, ndir));
								else if(dirs[ndir] == type[0]) nextStart.insert(make_tuple(nx, ny, ndir));
							}
						}
					}
				}
				for(auto &e: nexts) curq.push(e);
				nexts.clear();
			}
		}

		for(auto &e: nextStart) q.push(e);
		nextStart.clear();
	}

	set<tuple<int, int>> ans;
	while(!q.empty()) {
		ans.insert(make_pair(get<0>(q.front()), get<1>(q.front())));
		q.pop();
	}
	
	for(auto &e: ans) printf("%d %d\n", get<0>(e), get<1>(e));

	return 0;
}
