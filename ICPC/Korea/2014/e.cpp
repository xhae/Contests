#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n[3];
struct Point {
	int coord[2];
};
vector<Point> data[3], by[2][3];

int leftCnt[10000], rightCnt[10000];

vector<int> coords;
const int base = (1 << 15);
int iTree[base << 1];

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		for(int i = 0; i < 3; i++) {
			scanf("%d", n + i);
			data[i].resize(n[i]);
		}
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < n[i]; j++)
				scanf("%d %d", data[i][j].coord, data[i][j].coord + 1);
		
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 2; j++) {
				by[j][i] = data[i];
				sort(by[j][i].begin(), by[j][i].end(), [j](const Point &a, const Point &b) { return a.coord[j] < b.coord[j]; });
			}
		}

		int ans = 0;
		vector<int> order{0, 1, 2};
		do {
			int left = order[0], mid = order[1], right = order[2];

			for(int type = 0; type < 2; type++) {
				int leftInd = 0;
				while(leftInd < by[type][left].size() and by[type][left][leftInd].coord[type] < by[type][mid][0].coord[type]) leftInd++;
				leftCnt[0] = leftInd;
				for(int i = 1; i < by[type][mid].size(); i++) {
					while(leftInd < by[type][left].size() and by[type][left][leftInd].coord[type] < by[type][mid][i].coord[type]) leftInd++;
					leftCnt[i] = leftInd;
				}

				int rightInd = by[type][right].size() - 1;
				while(rightInd >= 0 and by[type][right][rightInd].coord[type] > by[type][mid].back().coord[type]) rightInd--;
				rightCnt[by[type][mid].size() - 1] = by[type][right].size() - 1 - rightInd;
				for(int i = by[type][mid].size() - 2; i >= 0; i--) {
					while(rightInd >= 0 and by[type][right][rightInd].coord[type] > by[type][mid][i].coord[type]) rightInd--;
					rightCnt[i] = by[type][right].size() - 1 - rightInd;
				}

				for(int i = 0; i < by[type][mid].size(); i++) 
					for(int j = i; j < by[type][mid].size(); j++)
						ans = max(ans, j - i + 1 + leftCnt[i] + rightCnt[j]);
			}
		} while(next_permutation(order.begin(), order.end()));

		do {
			coords.clear();
			int bot = order[0], left = order[1], right = order[2];
		} while(next_permutation(order.begin(), order.end()));
		printf("%d\n", ans);
	}

	return 0;
}
