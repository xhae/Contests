#include <cstdio>
#include <algorithm>

using namespace std;

long long iTree[1 << 20], buf[1 << 20];
const int base = (1 << 19);

int n, x;
long long data[500000];

void pushdown(int cs, int ce, int ind) {
	if(cs + 1 == ce) iTree[ind] += buf[ind];
	else {
		buf[ind * 2] += buf[ind];
		buf[ind * 2 + 1] += buf[ind];
		iTree[ind] = max(iTree[ind * 2] + buf[ind * 2], iTree[ind * 2 + 1] + buf[ind * 2 + 1]);
	}
	buf[ind] = 0;
}

const long long INF = 1000000ll * 1000000 * 100000;

long long update(int cs, int ce, int ts, int te, int ind, long long v) {
	if(cs >= ce or cs >= te or ts >= ce or ts >= te) return -INF;
	if(cs == ts and ce == te) {
		buf[ind] += v;
		v = 0;
	}

	pushdown(cs, ce, ind);

	if(v == 0) return iTree[ind];

	int mid = (cs + ce) / 2;
	long long ret = update(cs, mid, ts, min(te, mid), ind * 2, v);
	ret = max(ret, update(mid, ce, max(ts, mid), te, ind * 2 + 1, v));	

	return iTree[ind] = ret;
}

int getMaxStart(int cs, int ce, int ts, int te, int ind) {
	if(cs >= ce or cs >= te or ts >= ce or ts >= te) return -1;
	pushdown(cs, ce, ind);

	if(cs == ts and ce == te and iTree[ind] < x) return -1;

	if(cs + 1 == ce) return ind - base;
	else {
		int mid = (cs + ce) / 2;
		int v = getMaxStart(mid, ce, max(ts, mid), te, ind * 2 + 1);
		if(v >= 0) return v;
		return getMaxStart(cs, mid, ts, min(te, mid), ind * 2);
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &x);
		for(int i = 0; i < n; i++) scanf("%lld", data + i);
		
		fill(iTree, iTree + base * 2, 0);
		fill(buf, buf + base * 2, 0);

		int ans = -1;
		for(int i = 0; i < n; i++) {
			update(0, base, 0, i + 1, 1, data[i]);
			int ind = getMaxStart(0, base, 0, i + 1, 1);
			if(ind != -1) {
				if(ans == -1) ans = i - ind;
				else ans = min(ans, i - ind);
			}
		}

		if(ans != -1) ans++;
		printf("%d\n", ans);
	}

	return 0;
}
