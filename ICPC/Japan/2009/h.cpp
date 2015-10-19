#include <cstdio>
#include <algorithm>

using namespace std;

int m, n, data[128];
int dp[1 << 11][1 << 11];
int isVisited[1 << 11][1 << 11], kase;

int getAns(int asked, int answer) {
	int &ret = dp[asked][answer];
	if(isVisited[asked][answer] == kase) return ret;
	isVisited[asked][answer] = kase;

	int fit = 0;
	for(int i = 0; i < n; i++)
		if((data[i] & asked) == answer)
			fit++;
	if(fit == 0) ret = -2;
	else if(fit == 1) ret = 0;
	else {
		ret = 99999999;
		for(int i = 0; i < m; i++) {
			if(asked & (1 << i)) continue;
			int res[2] = {getAns(asked | (1 << i), answer), getAns(asked | (1 << i), answer | (1 << i))};
			ret = min(ret, max(res[0], res[1]) + 1);
		}
		if(ret == 99999999) ret = -2;
	}

	return ret;
}

int main(void) {
	while(scanf("%d %d", &m, &n), m > 0) {
		kase++;
		for(int i = 0; i < n; i++) {
			data[i] = 0;
			char str[12];
			scanf("%s", str);
			for(int j = 0; j < m; j++)
				if(str[j] == '1')
					data[i] |= (1 << j);
		}

		printf("%d\n", getAns(0, 0));
	}

	return 0;
}
