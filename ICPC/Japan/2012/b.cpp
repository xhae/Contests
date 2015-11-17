#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

int n, m;
string _ref[10], query[10];

int main(void) {
	while(cin >> n >> m, n > 0) {
		for(int i = 0; i < n; i++) cin >> _ref[i];
		for(int i = 0; i < m; i++) cin >> query[i];

		vector<tuple<int, int, int>> cands;
		for(int r = 1; r <= 20; r++)
			for(int c = 1; c <= 20; c++)
				for(int s = 1; s <= 20; s++) {
					int cnt[3] = {0, };
					bool isValid = true;
					for(int i = 0; i < n; i++) {
						int space = 0;
						while(_ref[i][space] == '.') space++;
						if(space != cnt[0] * r + cnt[1] * c + cnt[2] * s) {
							isValid = false;
							break;
						}
						while(space < _ref[i].size()) {
							char ch = _ref[i][space];
							if(ch == '(') cnt[0]++;
							else if(ch == ')') cnt[0]--;
							else if(ch == '{') cnt[1]++;
							else if(ch == '}') cnt[1]--;
							else if(ch == '[') cnt[2]++;
							else if(ch == ']') cnt[2]--;
							space++;
						}
					}

					if(isValid) cands.emplace_back(r, c, s);
				}

		int cnt[3] = {0, };
		for(int i = 0; i < m; i++) {
			int cand = -1;
			for(int j = 0; j < cands.size(); j++) {
				int r, c, s;
				tie(r, c, s) = cands[j];
				int cur = r * cnt[0] + c * cnt[1] + s * cnt[2];
				if(j == 0) cand = cur;
				else if(cand != cur) {
					cand = -1;
					break;
				}
			}

			printf("%d ", cand);
			int space = 0;
			while(space < query[i].size()) {
				char ch = query[i][space];
				if(ch == '(') cnt[0]++;
				else if(ch == ')') cnt[0]--;
				else if(ch == '{') cnt[1]++;
				else if(ch == '}') cnt[1]--;
				else if(ch == '[') cnt[2]++;
				else if(ch == ']') cnt[2]--;
				space++;
			}
		}

		printf("\n");
	}

	return 0;
}
