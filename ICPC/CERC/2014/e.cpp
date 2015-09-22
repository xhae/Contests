#include <cstdio>
#include <cstring>
#include <deque>

using namespace std;

int n, data[1000], sum[1000];
char dp[1001][1 << 13];
int isVisited[1001][1 << 13];
int _next[1000][1 << 13][2];
deque<int> prec[1 << 13];
int bitcnt[1 << 14], kase;

void compress(deque<int> &arg) {
	while(arg.size() > 1 and arg[0] == arg[1]) {
		arg[1] *= 2;
		arg.pop_front();
	}
	while(arg.size() > 1 and arg.back() == arg[arg.size() - 2]) {
		arg[arg.size() - 2] *= 2;
		arg.pop_back();
	}
}

int getLeft(deque<int> &arg) {
	int ret = 0, last = 0;
	for(int v: arg) {
		if(v < last) break;
		ret += v;
		last = v;
	}
	return ret;
}

char getAns(int nth, int bits) {
	if(nth == n) {
		if(sum[n - 1] == bits) return true;
		return false;
	}

	char &ret = dp[nth][bits];
	if(isVisited[nth][bits] == kase) return ret;
	isVisited[nth][bits] = kase;

	ret = false;
	if(nth == 0) {
		ret = getAns(nth + 1, data[0]);
		_next[0][bits][0] = data[0];
		_next[0][bits][1] = 0;
	} else {
		int cursum = sum[nth] - data[nth], otherBits = cursum - bits;
		deque<int> stats = prec[bits];
		for(int i = (int)prec[otherBits].size() - 1; i >= 0; i--) stats.push_back(prec[otherBits][i]);

		if(data[nth] <= stats.front()) {
			auto cand = stats;
			cand.push_front(data[nth]);
			compress(cand);
			if(getAns(nth + 1, getLeft(cand))) {
				ret = true;
				_next[nth][bits][0] = getLeft(cand);
				_next[nth][bits][1] = 0;
				return true;
			}
		}
		if(otherBits == 0 or data[nth] <= stats.back()) {
			auto cand = stats;
			cand.push_back(data[nth]);
			compress(cand);
			if(getAns(nth + 1, getLeft(cand))) {
				ret = true;
				_next[nth][bits][0] = getLeft(cand);
				_next[nth][bits][1] = 1;
				return true;
			}
		}
	}

	return ret;	
}

int main(void) {
	for(int i = 0; i < (1 << 14); i++)
		for(int j = 0; j < 14; j++)
			if(i & (1 << j))
				bitcnt[i]++;
	for(int i = 0; i < (1 << 13); i++)
		for(int j = 0; j < 13; j++)
			if(i & (1 << j)) prec[i].push_back(1 << j);

	int T;
	scanf("%d", &T);
	for(kase = 1; kase <= T; kase++) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d", data + i);
			sum[i] = data[i];
			if(i > 0) sum[i] += sum[i - 1];
		}
		
		if(bitcnt[sum[n - 1]] > 1) printf("no\n");
		else {
			if(getAns(0, 0)) {
				int cur = 0, bits = 0;
				while(cur < n) {
					printf("%c", _next[cur][bits][1] == 0 ? 'l' : 'r');
					int nbits = _next[cur][bits][0];
					cur++, bits = nbits;
				}
				printf("\n");
			} else printf("no\n");
		}
	}

	return 0;
}
