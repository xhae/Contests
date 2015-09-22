#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int dir[20], loc[20];

int main(void) {
	int n, l;
	while(scanf("%d %d", &n, &l), n > 0) {
		for(int i = 0; i < n; i++) {
			char temp[2];
			scanf("%s %d", temp, loc + i);
			if(temp[0] == 'R') dir[i] = 1;
			else dir[i] = -1;
			loc[i] *= 2;
		}

		int left = n, ans = -1, sec = 0;
		while(left > 0) {
			sec++;
			bool foundLeft = false;
			for(int i = 0; i < n; i++) {
				if(loc[i] > 0 and loc[i] < l * 2) {
					loc[i] += dir[i];
					if(loc[i] == 0) {
						ans = i;
						foundLeft = true;
						left--;
					} else if(loc[i] == l * 2) {
						left--;
						if(!foundLeft) ans = i;
					}
				}
			}

			for(int i = 0; i < n; i++) {
				if(loc[i] == 0 or loc[i] == l * 2) continue;
				for(int j = i + 1; j < n; j++) {
					if(loc[j] == 0 or loc[j] == l * 2) continue;
					if(loc[i] == loc[j]) {
						if(loc[i] % 2 == 0) {
							dir[i] *= -1;
							dir[j] *= -1;
						}
					}
				}
			}
		}

		printf("%d %d\n", sec / 2, ans + 1);
	}

	return 0;
}
