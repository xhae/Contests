#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <cstring>

using namespace std;

int n;
long long l, lefts[100000];

const int base = (1 << 17);
int iTree[base << 1], delta[base << 1];

void pushdown(int ind) {
	if(delta[ind] == -1) return;
	iTree[ind] = delta[ind];
	if(ind < base) delta[ind * 2] = delta[ind * 2 + 1] = delta[ind];
	delta[ind] = -1;
}

int getMin(int cs, int ce, int ts, int te, int ind) {
	if(cs >= ce || cs >= te || ts >= ce || ts >= te) return n + 1;
	pushdown(ind);
	
	if(cs == ts && ce == te) return iTree[ind];
	int mid = (cs + ce) / 2;
	return min(getMin(cs, mid, ts, min(te, mid), ind * 2), getMin(mid, ce, max(ts, mid), te, ind * 2 + 1));
}

void update(int cs, int ce, int ts, int te, int ind, int v) {
	if(cs >= ce || cs >= te || ts >= ce || ts >= te) return;	
	pushdown(ind);
	if(cs == ts && ce == te) {
		iTree[ind] = delta[ind] = v;
		return;
	}
	int mid = (cs + ce) / 2;
	update(cs, mid, ts, min(te, mid), ind * 2, v);
	update(mid, ce, max(ts, mid), te, ind * 2 + 1, v);
	iTree[ind] = min(iTree[ind * 2], iTree[ind * 2 + 1]);
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %lld", &n, &l);
		for(int i = 0; i < n; i++) scanf("%lld", lefts + i);	

		for(int i = 1; i < base * 2; i++) iTree[i] = n + 1;
		memset(delta, -1, sizeof(delta));

		bool isAble = true;
		for(int i = 0; i < n; i++) {
			int cur;
			scanf("%d", &cur);
			cur--;
			
			int lower = lower_bound(lefts, lefts + n, lefts[cur] - l) - lefts;
			int upper = upper_bound(lefts, lefts + n, lefts[cur] + l) - lefts;
						
			int minValue = getMin(0, base, lower, upper, 1);
			if(minValue < i - 1)
				isAble = false;

			update(0, base, lower, upper, 1, i);
		}

		if(isAble) printf("1\n");
		else printf("-1\n");
	}

	return 0;
}
