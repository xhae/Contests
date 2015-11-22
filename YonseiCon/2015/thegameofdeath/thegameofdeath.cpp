#include <cstdio>
#include <algorithm>

using namespace std;

int n, nexts[10001];
bool isVisited[10001];

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", nexts + i);

		fill(isVisited, isVisited + n + 1, false);
		
		int cur = 1;
		int ans = 0, cnt = 0;
		while(!isVisited[cur]) {
			isVisited[cur] = true;
			if(cur == n) {
				ans = cnt;
				break;
			}

			cur = nexts[cur];
			cnt++;
		}

		printf("%d\n", ans);
	}

	return 0;
}
