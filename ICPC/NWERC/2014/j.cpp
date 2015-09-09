#include <cstdio>
#include <string>
#include <map>

using namespace std;

map<string, int> cnt[2];
char temp[16];

int main(void) {
	int n;
	scanf("%d", &n);
	for(int type = 0; type < 2; type++)
		for(int i = 0; i < n; i++) {
			scanf("%s", temp);
			string judge = temp;
			cnt[type][temp]++;
		}

	int ans = 0;
	for(auto &e: cnt[0])
		if(cnt[1].count(e.first) > 0)
			ans += min(e.second, cnt[1][e.first]);

	printf("%d\n", ans);
	return 0;
}

