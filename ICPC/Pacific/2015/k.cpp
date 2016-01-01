#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cstring>
#include <queue>

using namespace std;

int n;
char field[26][27];
bool isVisited[26][26];

bool isPossible(int y, int x) {
	int whiteN = 0;
	map<pair<int, int>, set<pair<int, int>>> degree;
	set<pair<int, int>> covered;

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			whiteN += field[i][j] == 'W';

	queue<pair<int, int>> q;
	q.push(make_pair(y, x));
	memset(isVisited, 0, sizeof(isVisited));
	isVisited[y][x] = true;
	while(!q.empty()) {
		int cy = q.front().first, cx = q.front().second;
		q.pop();

		int mov[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
		for(int i = 0; i < 4; i++) {
			int ny = cy + mov[i][0] * 2, nx = cx + mov[i][1] * 2;
			if(ny < 0 or ny >= n or nx < 0 or nx >= n) continue;
			int wy = cy + mov[i][0], wx = cx + mov[i][1];
			if(field[wy][wx] == 'W' and field[ny][nx] == '_') {
				if(degree[make_pair(cy, cx)].count(make_pair(ny, nx)) == 0) {
					degree[make_pair(cy, cx)].insert(make_pair(ny, nx));
					degree[make_pair(ny, nx)].insert(make_pair(cy, cx));
					covered.insert(make_pair(wy, wx));
				}
				if(!isVisited[ny][nx]) {
					isVisited[ny][nx] = true;
					q.push(make_pair(ny, nx));
				}
			}
		}
	}

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(field[i][j] == 'W' and covered.count(make_pair(i, j)) == 0)
				return false;

	if(degree.size() > whiteN + 1) return false;
	int odds = 0;
	for(auto edges: degree)
		if(edges.second.size() % 2 == 1)
			odds++;
	if(odds == 0) return true;
	if(odds == 2 and degree[make_pair(y, x)].size() % 2 == 1) return true;
	return false;
}

int main(void) {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%s", field[i]);
	int ans[2] = {-1, -1};
	for(int i = 0; i < n and ans[0] != -2; i++)
		for(int j = 0; j < n and ans[0] != -2; j++)
			if(field[i][j] == 'B') {
				if(isPossible(i, j)) {
					if(ans[0] == -1) ans[0] = i, ans[1] = j;
					else ans[0] = -2;
				}
			}

	if(ans[0] == -1) printf("None\n");
	else if(ans[0] == -2) printf("Multiple\n");
	else printf("%c%d\n", (char)(ans[1] + 'a'), n - ans[0]);
	return 0;
}
