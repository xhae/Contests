#include <cstring>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>

using namespace std;

vector<int> child[100];
int dp[100][100][11][2];
int n, K;
char temp[10000];

int getAns(int nth, int childn, int leftK, int isWhite) {
	if(leftK < 0) return -(1 << 29);

	int &ret = dp[nth][childn][leftK][isWhite];
	if(ret != -1) return ret;

	if(childn == child[nth].size()) {
		if(leftK > 0) ret = -(1 << 29);
		else ret = isWhite;
	} else {
		ret = -(1 << 29);
		ret = max(ret, getAns(child[nth][childn], 0, K - (isWhite ? 0 : 1), 1) + getAns(nth, childn + 1, leftK, isWhite));
		if(isWhite == 0 or leftK > 0) ret = max(ret, getAns(child[nth][childn], 0, 0, 0) + getAns(nth, childn + 1, isWhite ? leftK - 1 : 0, isWhite));
	}

	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &K);
		for(int i = 0; i < n; i++) child[i].clear();
		gets(temp);
		for(int i = 0; i < n; i++) {
			gets(temp);
			string str = temp;
			istringstream it(str);
			int v;
			while(it >> v) {
				if(v == 0) break;
				child[i].push_back(v - 1);
			}
		}

		memset(dp, -1, sizeof(dp));
		printf("%d\n", max(getAns(0, 0, 0, 0), getAns(0, 0, K, 1)));
	}

	return 0;
}
