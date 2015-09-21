#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

vector<int> edges[500];
int type[500];
int n;

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) edges[i].clear();
		for(int i = 0; i < n; i++) {
			int p;
			scanf("%d", &p);
			while(p--) {
				int v;
				scanf("%d", &v);
				edges[i].push_back(v - 1);
			}
		}

		memset(type, -1, sizeof(type));
		int left = 0, right = 0;
		bool isPossible = true;
		for(int i = 0; i < n; i++) {
			if(type[i] >= 0) continue;
			type[i] = 0;
			int tot = 0, zeros = 0;
			
			queue<int> q;
			q.push(i);
			while(!q.empty()) {
				int cur = q.front();
				q.pop();

				tot++;
				zeros += type[cur] == 0;

				for(int next: edges[cur]) {
					if(type[next] >= 0) {
						if(type[next] == type[cur]) {
							isPossible = false;
							break;
						}
					} else {
						type[next] = !type[cur];
						q.push(next);
					}
				}
			}

			if(!isPossible) break;
			left += min(zeros, tot - zeros);
			right += max(zeros, tot - zeros);
		}

		printf("Case %d: ", kase);
		if(!isPossible) printf("0 0 0\n");
		else printf("1 %d %d\n", left, right);
	}

	return 0;
}



