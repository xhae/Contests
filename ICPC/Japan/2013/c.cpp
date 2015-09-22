#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

vector<int> xs, ys;
int n;

int data[50][4];
bool blVert[102][102], blHori[102][102];

int main(void) {
	while(scanf("%d", &n), n > 0) {
		xs = vector<int>{-1, 1000001};
		ys = vector<int>{-1, 1000001};

		for(int i = 0; i < n; i++) {
			for(int j = 0; j < 4; j++) scanf("%d", data[i] + j);
			swap(data[i][1], data[i][3]);

			xs.push_back(data[i][0]);
			xs.push_back(data[i][2]);
			ys.push_back(data[i][1]);
			ys.push_back(data[i][3]);
		}

		sort(xs.begin(), xs.end());
		sort(ys.begin(), ys.end());
		xs.erase(unique(xs.begin(), xs.end()), xs.end());
		ys.erase(unique(ys.begin(), ys.end()), ys.end());

		for(int i = 0; i < n; i++)
			for(int j = 0; j < 4; j++)
				if(j % 2 == 0) data[i][j] = lower_bound(xs.begin(), xs.end(), data[i][j]) - xs.begin();
				else data[i][j] = lower_bound(ys.begin(), ys.end(), data[i][j]) - ys.begin();

		memset(blVert, 0, sizeof(blVert));
		memset(blHori, 0, sizeof(blHori));

		for(int i = 0; i < n; i++) {
			for(int j = data[i][0]; j < data[i][2]; j++) {
				blHori[data[i][1]][j] = true;
				blHori[data[i][3]][j] = true;
			}
			for(int j = data[i][1]; j < data[i][3]; j++) {
				blVert[j][data[i][0]] = true;
				blVert[j][data[i][2]] = true;
			}
		}

		bool isChecked[101][101] = {false, };
		int ans = 0;
		for(int i = 0; i < ys.size() - 1; i++) {
			for(int j = 0; j < xs.size() - 1; j++) {
				if(isChecked[i][j]) continue;
				ans++;
				queue<pair<int, int>> q;
				q.push(make_pair(i, j));
				isChecked[i][j] = true;
				while(!q.empty()) {
					int cy = q.front().first, cx = q.front().second;
					q.pop();

					if(cy + 1 < ys.size() - 1 and !blHori[cy + 1][cx]) {
						int ny = cy + 1;
						int nx = cx;
						if(!isChecked[ny][nx]) {
							isChecked[ny][nx] = true;
							q.push(make_pair(ny, nx));
						}
					}

					if(cy - 1 >= 0 and !blHori[cy][cx]) {
						int ny = cy - 1;
						int nx = cx;
						if(!isChecked[ny][nx]) {
							isChecked[ny][nx] = true;
							q.push(make_pair(ny, nx));
						}
					}

					if(cx + 1 < xs.size() - 1 and !blVert[cy][cx + 1]) {
						int ny = cy;
						int nx = cx + 1;
						if(!isChecked[ny][nx]) {
							isChecked[ny][nx] = true;
							q.push(make_pair(ny, nx));
						}
					}

					if(cx - 1 >= 0 and !blVert[cy][cx]) {
						int ny = cy;
						int nx = cx - 1;
						if(!isChecked[ny][nx]) {
							isChecked[ny][nx] = true;
							q.push(make_pair(ny, nx));
						}
					}
				}
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}
