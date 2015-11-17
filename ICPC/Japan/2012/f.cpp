#include <cstdio>
#include <stack>

using namespace std;

int n, m;
long long parent[100000][2];

stack<int> st;

int getParent(int u) {
	int cur = u;
	while(parent[cur][0] != cur) {
		st.push(cur);
		cur = parent[cur][0];
	}

	int top = cur;
	long long relWeight = 0;
	while(!st.empty()) {
		cur = st.top();
		st.pop();
		parent[cur][0] = top;
		relWeight += parent[cur][1];
		parent[cur][1] = relWeight;
	}

	return top;
}

int main(void) {
	while(scanf("%d %d", &n, &m), n > 0) {
		for(int i = 0; i < n; i++) {
			parent[i][0] = i;
			parent[i][1] = 0;
		}

		char type[2];
		for(int i = 0; i < m; i++) {
			int u, v, c;
			scanf("%s %d %d", type, &u, &v);
			u--, v--;
			int pu = getParent(u);
			int pv = getParent(v);

			if(type[0] == '!') {
				scanf("%d", &c);
				if(pu == pv) continue;
				else {
					parent[pv][0] = pu;
					parent[pv][1] = c + parent[u][1] - parent[v][1];
				}
			} else {
				if(pu != pv) printf("UNKNOWN\n");
				else printf("%lld\n", parent[v][1] - parent[u][1]);
			}
		}
	}

	return 0;
}
