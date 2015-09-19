#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

int n, parent[1000000], salary[1000000];
int range[1000000][2], noden;
vector<int> child[1000000];

void dfs(int u) {
	range[u][0] = noden++;
	for(int v: child[u]) dfs(v);
	range[u][1] = noden;
}

const int base = (1 << 20);
int maxTree[base << 1], maxBuf[base << 1], minTree[base << 1], minBuf[base << 1];

void pushdown(int *tree, int *buf, int ind) {
	tree[ind] += buf[ind];
	if(ind * 2 < base * 2) {
		buf[ind * 2] += buf[ind];
		buf[ind * 2 + 1] += buf[ind];
	}
	buf[ind] = 0;
}

void update(int *tree, int *buf, function<int(int, int)> cmp, int cs, int ce, int ts, int te, int ind, int v) {
	if(cs >= ce or cs >= te or ts >= ce or ts >= te) return;
	if(cs == ts and ce == te) {
		buf[ind] += v;
		v = 0;
	}

	pushdown(tree, buf, ind);
	if(v > 0) {
		int mid = (cs + ce) / 2;
		update(tree, buf, cmp, cs, mid, ts, min(te, mid), ind * 2, v);
		update(tree, buf, cmp, mid, ce, max(ts, mid), te, ind * 2 + 1, v);
		tree[ind] = cmp(tree[ind * 2] + buf[ind * 2], tree[ind * 2 + 1] + buf[ind * 2 + 1]);
	}
}

int getVal(int *tree, int *buf, function<int(int, int)> cmp, int cs, int ce, int ts, int te, int ind) {
	if(cs >= ce or cs >= te or ts >= ce or ts >= te) return 0 - cmp(1 << 29, -(1 << 29));
	pushdown(tree, buf, ind);
	
	if(cs == ts and ce == te) return tree[ind];
	int mid = (cs + ce) / 2;
	return cmp(	getVal(tree, buf, cmp, cs, mid, ts, min(te, mid), ind * 2),
				getVal(tree, buf, cmp, mid, ce, max(ts, mid), te, ind * 2 + 1));
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		memset(parent, -1, sizeof(parent));
		scanf("%d", &n);
		for(int i = 0; i < n; i++) child[i].clear();
		for(int i = 1; i < n; i++) {
			int p;
			scanf("%d", &p);
			parent[i] = p - 1;
			child[p - 1].push_back(i);
		}

		noden = 0;
		dfs(0);

		fill(maxTree, maxTree + base * 2, 0);
		fill(maxBuf, maxBuf + base * 2, 0);
		fill(minTree, minTree + base * 2, 0);
		fill(minBuf, minBuf + base * 2, 0);

		auto maxCmp = [](int a, int b) { return max(a, b); };
		auto minCmp = [](int a, int b) { return min(a, b); };

		for(int i = 0; i < n; i++) {
			scanf("%d", salary + i);
			update(maxTree, maxBuf, maxCmp, 0, base, range[i][0], range[i][0] + 1, 1, salary[i]);
			update(minTree, minBuf, minCmp, 0, base, range[i][0], range[i][0] + 1, 1, salary[i]);
		}

		int qn;
		scanf("%d", &qn);
		while(qn--) {
			char type[2];
			int op[2];
			scanf("%s %d", type, op);
			op[0]--;
			if(type[0] == 'R') {
				scanf("%d", op + 1);
				update(maxTree, maxBuf, maxCmp, 0, base, range[op[0]][0], range[op[0]][1], 1, op[1]);
				update(minTree, minBuf, minCmp, 0, base, range[op[0]][0], range[op[0]][1], 1, op[1]);
			} else {
				int Mv = getVal(maxTree, maxBuf, maxCmp, 0, base, range[op[0]][0], range[op[0]][1], 1);
				int mv = getVal(minTree, minBuf, minCmp, 0, base, range[op[0]][0], range[op[0]][1], 1);
				printf("%d\n", Mv - mv);
			}
		}
	}

	return 0;
}
