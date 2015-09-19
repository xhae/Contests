#include <cstdio>
#include <cstring>

char dp[100][100][101];
int n, data[100], oneInd;

char isWin(int s, int e, int buf) {
	char &ret = dp[s][e][buf];
	if(ret != -1) return ret;

	ret = false;
	if(s == e) ret = true;
	if(buf > 0 and !isWin(s, e, buf - 1)) ret = true;
	for(int i = s; i <= e; i++) {
		int bef = i - 1, aft = i + 1;
		bool isPossible = true;
		if(bef >= s and bef <= e and data[bef] > data[i]) isPossible = false;
		if(aft >= s and aft <= e and data[aft] > data[i]) isPossible = false;
		if(isPossible) {
			if(oneInd < i and !isWin(s, i - 1, buf + (e - i))) ret = true;
			if(oneInd > i and !isWin(i + 1, e, buf + (i - s))) ret = true;
		}
	}

	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d", data + i);
			if(data[i] == 1) oneInd = i;
		}
		memset(dp, -1, sizeof(dp));
		printf("%s\n", isWin(0, n - 1, 0) ? "Alice" : "Bob");
	}

	return 0;
}
