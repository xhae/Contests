#include <cstdio>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

int n, m;
tuple<int, int, int> edges[100000];

const int base = (1 << 17);
pair<int, int> iTree[base << 1];
int delta[base << 1];
int ans[100000][2];

void pushdown(int cs, int ce, int ind) {
	iTree[ind].first += delta[ind];
	if(cs + 1 < ce) {
		delta[ind * 2] += delta[ind];
		delta[ind * 2 + 1] += delta[ind];
	}

	delta[ind] = 0;
}

pair<int, int> getMax(int cs, int ce, int ts, int te, int ind) {
	if(cs >= ce or cs >= te or ts >= ce or ts >= te) return make_pair(0, 0);
	pushdown(cs, ce, ind);
	if(cs == ts and ce == te) return iTree[ind];

	int mid = (cs + ce) / 2;
	return max(getMax(cs, mid, ts, min(te, mid), ind * 2), getMax(mid, ce, max(ts, mid), te, ind * 2 + 1));
}

void update(int cs, int ce, int ts, int te, int ind, int v) {
	if(cs >= ce or cs >= te or ts >= ce or ts >= te) return;
	pushdown(cs, ce, ind);
	if(cs == ts and ce == te) {
		delta[ind] += v;
		pushdown(cs, ce, ind);
	} else {
		int mid = (cs + ce) / 2;
		update(cs, mid, ts, min(te, mid), ind * 2, v);
		update(mid, ce, max(ts, mid), te, ind * 2 + 1, v);
		iTree[ind] = max(iTree[ind * 2], iTree[ind * 2 + 1]);
	}
}

int usedCnt[100000];

int main(void) {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int cost, used, ind = i;
		scanf("%d %d", &cost, &used);
		used = !used;
		edges[i] = make_tuple(cost, used, ind);
	}

	sort(edges, edges + m);
/*
	for(int i = 0; i < n; i++) {
		int ind = base + i;
		iTree[ind].second = i;
		ind /= 2;
		while(ind >= 1) {
			iTree[ind] = max(iTree[ind * 2], iTree[ind * 2 + 1]);
			ind /= 2;
		}
	}
*/
	bool isValid = true;
	int have = 1;
	for(int i = 0; i < m; i++) {
		int cost, used, ind;
		tie(cost, used, ind) = edges[i];

		if(used == 0) {
			/*
			auto maxVal = getMax(0, base, 0, have, 1);
			update(0, base, 0, maxVal.second, 1, 1);
			update(0, base, maxVal.second + 1, have, 1);
			update(0, base, have, have + 1, 1, have - 2);
*/
			have++;
			ans[ind][0] = 1;
			ans[ind][1] = have;
		} else {
			/*
			auto maxVal = getMax(0, base, 0, have, 1);
			if(maxVal.first == 0) {
				isValid = false;
				break;
			} else {
				auto maxVal2 = getMax(0, base, 0, maxVal.second, 1);
				maxVal2 = max(maxVal2, getMax(0, base, 0, maxVal.second + 1, 1));

				if(maxVal2.first == 0) {
					isValid = false;
					break;
				}

				ans[ind][0] = maxVal.second + 1;
				ans[ind][1] = maxVal2.second + 1;

				update(0, base, maxVal.second, maxVal.second + 1, 
			}*/

			bool found = false;
			for(int j = 1; j < have; j++)
				if(usedCnt[j] < have - (j + 1)) {
					usedCnt[j]++;
					ans[ind][0] = j + 1;
					ans[ind][1] = j + 1 + usedCnt[j];
					found = true;
					break;
				}
			if(!found) {
				isValid = false;
				break;
			}
		}
	}

	if(!isValid) printf("-1\n");
	else {
		for(int i = 0; i < m; i++) printf("%d %d\n", ans[i][0], ans[i][1]);
	}
	return 0;
}
