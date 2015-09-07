#include <cstdio>
#include <map>

using namespace std;

map<pair<int, int>, int> labeled;
int cnt[6];
int mov[6][2] = {{0, 1}, {1, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 0}};

int main(void) {
	int ans[10000];
	pair<int, int> cur{0, 0};
	cnt[1]++;
	labeled[cur] = 1;
	ans[0] = 1;
	int nth = 1;
	int unit = 1;
	while(nth < 10000) {
		for(int dir = 0; dir < 6 and nth < 10000; dir++) {
			int lim = unit;
			if(dir == 1) lim--;
			for(int i = 0; i < lim and nth < 10000; i++) {
				cur.first += mov[dir][0];
				cur.second += mov[dir][1];

				bool used[6] = {false, };
				for(int j = 0; j < 6; j++) {
					int ny = cur.first + mov[j][0];
					int nx = cur.second + mov[j][1];
					if(labeled.count(make_pair(ny, nx)) > 0) 
						used[labeled[make_pair(ny, nx)]] = true;
				}

				int tar = -1, tarcnt = 99999999;
				for(int j = 1; j <= 5; j++)
					if(used[j] == false and cnt[j] < tarcnt) {
						tarcnt = cnt[j];
						tar = j;
					}
				
				cnt[tar]++;
				labeled[cur] = tar;
				ans[nth++] = tar;
			}
		}
		unit++;
	}


	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", ans[n - 1]);
	}

	return 0;
}
