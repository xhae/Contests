#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <tuple>

using namespace std;

const long long P = 9705276, Q = 12805858;
int cnt[401][401];

int pn = -1, qn = -1;
long long tot = 0;

int n;

int dp[201][201][201];
unsigned char _next[201][201][201][3];
bool isVisited[201][201][201];

int getAns(int curp, int curq, int oppp) {
	if((curp + curq + 1) * 2 > tot) return 0;

	int &ret = dp[curp][curq][oppp];
	if(isVisited[curp][curq][oppp]) return ret;
	isVisited[curp][curq][oppp] = true;

	ret = -1;

	for(int front = 0; front < 2; front++) {
		int nextp = curp + 1 - front;
		int nextq = curq + front;
		if(nextp > pn or nextq > qn) continue;

		for(int back = 0; back < 2; back++) {
			int noppp = oppp + 1 - back;
			int noppq = curp + curq - oppp + back;

			if(noppp > pn - nextp or noppq > qn - nextq) continue;

			static vector<pair<int, int>> cands;
			cands.resize(4);
			cands[0] = make_pair(nextp, nextq);
			cands[1] = make_pair(pn - nextp, qn - nextq);
			cands[2] = make_pair(noppp, noppq);
			cands[3] = make_pair(pn - noppp, qn - noppq);

			int base = 0;
			for(int i = 0; i < cands.size(); i++) {
				bool existed = false;
				for(int j = 0; j < i; j++)
					if(cands[i] == cands[j]) {
						existed = true;
						break;
					}
				if(!existed) base += cnt[cands[i].first][cands[i].second];
			}

			int res = base + getAns(nextp, nextq, noppp);
			if(res > ret) {
				ret = res;
				_next[curp][curq][oppp][0] = nextp;
				_next[curp][curq][oppp][1] = nextq;
				_next[curp][curq][oppp][2] = noppp;
			}
		}
	}

	return ret;
}

vector<tuple<long long, int, int>> pre;

int main(void) {
	for(int i = 0; i <= 400; i++)
		for(int j = 0; j <= 400; j++)
			pre.push_back(make_tuple(P * i + Q * j, i, j));

	sort(pre.begin(), pre.end());

	scanf("%d", &n);

	long long totv = 0;

	while(n--) {
		long long a, b;
		scanf("%lld.%lld", &a, &b);
		a = a * 100000 + b;
		
		int ind = lower_bound(pre.begin(), pre.end(), make_tuple(a, 0, 0)) - pre.begin();
		int cpi = -1, cqi;

		if(ind < pre.size() and get<0>(pre[ind]) == a) {
			cpi = get<1>(pre[ind]);
			cqi = get<2>(pre[ind]);
		}
		
		if(cpi >= 0) {
			if(totv < a) {
				totv = a;
				tot = cpi + cqi;
				pn = cpi, qn = cqi;
			}
			cnt[cpi][cqi] = 1;
		}
	}

	getAns(0, 0, 0);

	int cur[3] = {0, 0, 0};
	string str;
	str.resize(tot);
	for(int i = 0; i < tot / 2; i++) {
		int nstat[3];
		for(int j = 0; j < 3; j++) nstat[j] = _next[cur[0]][cur[1]][cur[2]][j];
		if(nstat[0] != cur[0]) str[i] = 'P';
		else str[i] = 'Q';
		if(nstat[2] != cur[2]) str[tot - i - 1] = 'P';
		else str[tot - i - 1] = 'Q';
		cur[0] = nstat[0], cur[1] = nstat[1], cur[2] = nstat[2];
	}

	if(tot % 2 == 1) {
		if(cur[0] + cur[2] != pn) str[tot / 2] = 'P';
		else str[tot / 2] = 'Q';
	}

	printf("%s\n", str.c_str());

	return 0;
}
