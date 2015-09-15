#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long dp[2][201][201];
int n;
vector<pair<long long, long long>> data[2];
const long long INF = (1ll << 60);

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

		for(int i = 0; i <= data[0].size(); i++)
			for(int j = 0; j <= data[1].size(); j++)
				dp[0][i][j] = dp[1][i][j] = INF;

		dp[0][0][0] = dp[1][0][0] = 0;
		for(int i = 0; i <= data[0].size(); i++)
			for(int j = 0; j <= data[1].size(); j++) {
				long long start = dp[0][i][j], ed = 0;
				for(int k = i; k < data[0].size(); k++) {
					start = max(start, data[0][k].first);
					ed = max(ed, start + data[0][k].second);
					dp[1][k + 1][j] = min(dp[1][k + 1][j], ed);
					start += 10, ed += 10;
				}
			
				start = dp[1][i][j], ed = 0;
				for(int k = j; k < data[1].size(); k++) {
					start = max(start, data[1][k].first);
					ed = max(ed, start + data[1][k].second);
					dp[0][i][k + 1] = min(dp[0][i][k + 1], ed);
					start += 10, ed += 10;
				}
			}
		
		printf("%lld\n", min(dp[0][data[0].size()][data[1].size()], dp[1][data[0].size()][data[1].size()]));
	}

	return 0;
}
