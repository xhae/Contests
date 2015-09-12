#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int iTree[1 << 16];
const int base = (1 << 15);

int n, K, data[20000], sorted[20000];

bool sortf(const int &a, const int &b) {
	int zoneA = (a + K - 1) / K;
	int zoneB = (b + K - 1) / K;
	if(zoneA == zoneB) return false;
	return a < b;
}

int goalInd[20001], origInd[20001];

int getSum(int ind) {
	ind += base;
	int ret = 0;
	while(ind > 0) {
		ret += iTree[ind];
		ind /= 2;
	}
	return ret;
}

void addOne(int cs, int ce, int ts, int te, int ind) {
	if(cs == ts and ce == te) {
		iTree[ind]++;
		return;
	}
	if(cs >= ce or cs >= te or ts >= ce or ts >= te) return;

	int mid = (cs + ce) / 2;
	addOne(cs, mid, ts, min(te, mid), ind * 2);
	addOne(mid, ce, max(ts, mid), te, ind * 2 + 1);
}

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		fill(iTree, iTree + base * 2, 0);
		scanf("%d %d", &n, &K);
		for(int i = 0; i < n; i++) {
			scanf("%d", data + i);
			origInd[data[i]] = i;
			sorted[i] = data[i];
		}
		stable_sort(sorted, sorted + n, sortf);
		for(int i = 0; i < n; i++) goalInd[sorted[i]] = i;

		long long ans[2] = {0, 0};
		for(int i = 0; i < n; i++) {
			int cur = sorted[i];
			int curInd = getSum(origInd[cur]) + origInd[cur];
			int tarInd = goalInd[cur];
			ans[0] += curInd > tarInd ? curInd - tarInd : 0;

			addOne(0, base, 0, origInd[cur], 1);
		}

		ans[1] = 0;
		for(int i = 0; i < n; i++) {
			long long gap = goalInd[data[i]] - origInd[data[i]];
			if(gap < 0) gap *= -1;
			ans[1] = max(ans[1], gap);
		}

		printf("Case %d: %lld\n", kase, ans[0] - ans[1]);
	}

	return 0;
}
