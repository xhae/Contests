#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long dp[2][201][201];
int n;

vector<pair<long long, long long>> data[2];

const long long INF = (1ll << 60);

long long getAns(int type, int ai, int bi) {
	long long &ret = dp[type][ai][bi];
	if(ret != -1) return ret;

	if(ai == 0 and bi == 0) ret = 0;
	else if(ai == 0) {
		if(type == 0) ret = INF;
		else {
			ret = data[1][0].first + data[1][0].second;
			for(int i = 1; i < bi; i++) {
				:		
			}
		}
	} else if(bi == 0) {
		if(type == 1) ret = INF;
		else {

		}
	} else {

	}

	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		data[0].clear(), data[1].clear();
		for(int i = 0; i < n; i++) {
			long long s, t;
			char type[2];
			scanf("%s %lld %lld", type, &s, &t);
			if(type[0] == 'A') data[0].push_back(make_pair(s, t));
			else data[1].push_back(make_pair(s, t));
		}

		memset(dp, -1, sizeof(dp));
		printf("%lld\n", min(getAns(0, data[0].size(), data[1].size()), getAns(1, data[0].size(), data[1].size()));
	}

	return 0;
}
