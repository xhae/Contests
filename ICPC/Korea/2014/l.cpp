#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cstring>

using namespace std;

vector<long long> coords;

int n;
long long data[10000][3], dp[20000][101];
unordered_map<long long, int> chash;
vector<int> nthsInTime[10000];
vector<int> curOrders[20000];

long long getAns(int coord, int orderInd) {
	long long &ret = dp[coord][orderInd];
	if(ret != -1) return ret;

	ret = 0;
	if(coord < coords.size() - 1) {
		if(orderInd == curOrders[coord].size()) {
			ret = max(ret, getAns(coord + 1, curOrders[coord + 1].size()));
			for(int i = 0; i < curOrders[coord].size(); i++) {
				int norder = curOrders[coord][i];
				if(data[norder][0] != coord) continue;
				ret = max(ret, data[norder][2] + getAns(coord, i));
			}
		} else {
			int curOrder = curOrders[coord][orderInd];
			if(data[curOrder][1] == coord + 1) ret = max(ret, getAns(coord + 1, curOrders[coord + 1].size()));
			else {
				int nthFromStart = coord + 1 - data[curOrder][0];
				ret = max(ret, getAns(coord + 1, nthsInTime[curOrder][nthFromStart]));
			}

			for(int i = 0; i < curOrders[coord].size(); i++) {
				int norder = curOrders[coord][i];
				if(norder == curOrder) continue;
				if(data[norder][0] != coord) continue;
				int curEnd = data[curOrder][1];
				int nEnd = data[norder][1];

				if(curEnd < nEnd) ret = max(ret, data[norder][2] + getAns(curEnd, nthsInTime[norder][curEnd - data[norder][0]]));
				else if(curEnd > nEnd) ret = max(ret, data[norder][2] + getAns(nEnd, nthsInTime[curOrder][nEnd - data[curOrder][0]]));
				else ret = max(ret, data[norder][2] + getAns(curEnd, curOrders[curEnd].size()));
			}
		}
	}

	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		coords.clear();
		for(int i = 0; i < n; i++) {
			scanf("%lld %lld %lld", data[i], data[i] + 1, data[i] + 2);
			coords.push_back(data[i][0]);
			coords.push_back(data[i][1] + 1);
		}

		sort(coords.begin(), coords.end());
		coords.erase(unique(coords.begin(), coords.end()), coords.end());
		chash.clear();
		for(int i = 0; i < coords.size(); i++) chash[coords[i]] = i;		
		for(int i = 0; i < n; i++) {
			data[i][0] = chash[data[i][0]];
			data[i][1] = chash[data[i][1] + 1];
		}

		for(int i = 0; i < coords.size(); i++) curOrders[i].clear();
		for(int i = 0; i < n; i++) nthsInTime[i].clear();

		for(int i = 0; i < n; i++)
			for(int j = data[i][0]; j < data[i][1]; j++) {
				nthsInTime[i].push_back((int)curOrders[j].size());
				curOrders[j].push_back(i);
			}

		memset(dp, -1, sizeof(dp));
		printf("%lld\n", getAns(0, curOrders[0].size()));
	}

	return 0;
}
