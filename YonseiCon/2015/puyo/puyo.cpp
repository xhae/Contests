#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> makeNext(vector<string> field) {
	for(int y = 0; y < field.size(); y++)
		for(int x = 0; x < field[y].size(); x++) {
			if(field[y][x] == '.') continue;
			vector<pair<int, int>> q;
			char cur = field[y][x];
			int mov[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
			q.emplace_back(y, x);
			field[y][x] = '.';
			for(int i = 0; i < q.size(); i++) {
				int cy = q[i].first, cx = q[i].second;
				for(int j = 0; j < 4; j++) {
					int ny = cy + mov[j][0], nx = cx + mov[j][1];
					if(ny >= 0 and ny < 12 and nx >= 0 and nx < 6 and field[ny][nx] == cur) {
						field[ny][nx] = '.';
						q.emplace_back(ny, nx);
					}
				}
			}

			if(q.size() < 4)
				for(auto coord: q)
					field[coord.first][coord.second] = cur;
		}

	vector<string> ret(12, "......");
	for(int x = 0; x < 6; x++) {
		int ind = 11;
		for(int y = 11; y >= 0; y--)
			if(field[y][x] != '.') 
				ret[ind--][x] = field[y][x];
	}

	return ret;
}

int main(void) {
	vector<string> field(12);
	for(int i = 0; i < 12; i++) cin >> field[i];

	int ans = 0;
	while(true) {
		auto next = makeNext(field);
		if(next == field) break;
		field = next;
		ans++;
	}

	printf("%d\n", ans);
	return 0;
}
