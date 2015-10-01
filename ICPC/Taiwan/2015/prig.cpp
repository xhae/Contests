#include <cstdio>
#include <vector>

using namespace std;

const int base = (1 << 17);
vector<int> iTree[base << 1];

int getAns(int cs, int ce, int ts, int te, int ind, int sy, int ey) {
	if(cs >= ce or cs >= te or ts >= ce or ts >= te) return 0;
	if(cs == ts and ce == te) return upper_bound(iTree[ind].begin(), iTree[ind].end(), ey) - lower_bound(iTree[ind].begin(), iTree[ind].end(), sy);

	int mid = (cs + ce) / 2;
	return getAns(cs, mid, ts, min(te, mid), ind * 2, sy, ey) + getAns(mid, ce, max(ts, mid), te, ind * 2 + 1, sy, ey);
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		for(int i = base; i < base * 2; i++) iTree[i].clear();

		int n, m;
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			iTree[x + base].push_back(y);
		}
		for(int i = base; i < base * 2; i++) sort(iTree[i].begin(), iTree[i].end());
		int s = base / 2;
		while(s > 0) {
			for(int cur = s; cur < s * 2; cur++) {
				auto &tar = iTree[cur];
				auto &c1 = iTree[cur * 2], &c2 = iTree[cur * 2 + 1];

				tar.clear();
				int i1 = 0, i2 = 0;
				while(i1 < c1.size() and i2 < c2.size()) {
					if(c1[i1] < c2[i2]) tar.push_back(c1[i1++]);
					else tar.push_back(c2[i2++]);
				}
				while(i1 < c1.size()) tar.push_back(c1[i1++]);
				while(i2 < c2.size()) tar.push_back(c2[i2++]);
			}

			s /= 2;
		}

		long long ans = 0;
		while(m--) {
			int sx, sy, ex, ey;
			scanf("%d %d %d %d", &sx, &ex, &sy, &ey);
			ans += getAns(0, base, sx, ex + 1, 1, sy, ey);
		}

		printf("%lld\n", ans);
	}

	return 0;
}
