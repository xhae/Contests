#include <cstdio>
#include <string>
#include <algorithm>
#include <cstring>
#include <map>
#include <queue>

using namespace std;

char inp[200][51];
bool field[202][202];
int h, w, id[202][202], idn;
const int mov[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int main(void) {
	int kase = 0;
	while(scanf("%d %d", &h, &w), h > 0) {
		for(int i = 0; i < h; i++) {
			scanf("%s", inp[i]);
			for(int j = 0; j < w; j++) {
				if(inp[i][j] <= '9') inp[i][j] -= '0';
				else inp[i][j] -= ('a' - 10);
				for(int k = 0; k < 4; k++)
					field[i + 1][j * 4 + k + 1] = (inp[i][j] & (1 << (3 - k))) ? true: false;
			}
		}

		memset(id, -1, sizeof(id));
		idn = 0;
		w = w * 4 + 2;
		h += 2;
		for(int i = 0; i < w; i++) field[0][i] = field[h - 1][i] = false;
		for(int i = 0; i < h; i++) field[i][0] = field[i][w - 1] = false;

		for(int i = 0; i < h; i++)
			for(int j = 0; j < w; j++)
				if(field[i][j] == true and id[i][j] == -1) {
					queue<pair<int, int>> q;
					q.push(make_pair(i, j));
					id[i][j] = ++idn;
					while(!q.empty()) {
						int y = q.front().first, x = q.front().second;
						q.pop();
						
						for(int k = 0; k < 4; k++) {
							int ny = y + mov[k][0], nx = x + mov[k][1];
							if(ny >= 0 and ny < h and nx >= 0 and nx < w and id[ny][nx] == -1 and field[ny][nx]) {
								id[ny][nx] = idn;
								q.push(make_pair(ny, nx));
							}
						}
					}
				}

		idn++;
		map<int, int> adjcnt;
		for(int i = 1; i < idn; i++) adjcnt[i] = 0;

		for(int i = 0; i < h; i++)
			for(int j = 0; j < w; j++)
				if(field[i][j] == false and id[i][j] == -1) {
					map<int, int> adjed;
					queue<pair<int, int>> q;
					q.push(make_pair(i, j));
					id[i][j] = idn;
					bool isAble = true;
					while(!q.empty()) {
						int y = q.front().first, x = q.front().second;
						q.pop();
						for(int k = 0; k < 4; k++) {
							int ny = y + mov[k][0], nx = x + mov[k][1];
							if(ny >= 0 and ny < h and nx >= 0 and nx < w) {
								if(field[ny][nx]) adjed[id[ny][nx]] = 0;
								else if(id[ny][nx] == -1) {
									id[ny][nx] = idn;
									q.push(make_pair(ny, nx));
								}
							} else isAble = false;
						}
					}

					if(isAble and adjed.size() == 1) for(auto v: adjed) adjcnt[v.first]++;
				}

		char cands[10] = {0, };
		cands[2] = 'A';
		cands[4] = 'J';
		cands[6] = 'D';
		cands[5] = 'S';
		cands[1] = 'W';
		cands[3] = 'K';

		string ans;
		for(auto v: adjcnt) ans += cands[v.second + 1];
		sort(ans.begin(), ans.end());
		printf("Case %d: %s\n", ++kase, ans.c_str());
	}

	return 0;
}
