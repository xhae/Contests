#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

int n;
long long cost[14][14], l;

unordered_set<long long> rightCosts;
int left, right;

vector<int> lefts;
vector<int> bits[1 << 14];

vector<pair<long long, long long>> calced[1 << 14][14];

void calcRight(int stat, int leftLast) {
	rightCosts.clear();
	if(calced[stat][bits[stat][0]].size() > 0) {
		for(int first: bits[stat])
			for(auto &e: calced[stat][first]) {
				e.first += -e.second + cost[leftLast][first];
				e.second = cost[leftLast][first];
				rightCosts.insert(e.first);
			}
		return;
	}

	auto ord = bits[stat];
	do {
		long long cur = cost[ord.back()][0];
		for(int i = 0; i < ord.size(); i++) {
			int bef = (i == 0 ? leftLast : ord[i - 1]);
			cur += cost[bef][ord[i]];
		}

		rightCosts.insert(cur);
		calced[stat][ord[0]].push_back(make_pair(cur, cost[leftLast][ord[0]]));
	} while(next_permutation(ord.begin(), ord.end()));
}

int main(void) {
	for(int i = 0; i < (1 << 14); i++)
		for(int j = 0; j < 14; j++)
			if(i & (1 << j))
				bits[i].push_back(j);

	scanf("%d %lld", &n, &l);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scanf("%lld", cost[i] + j);

	if(n <= 3) {
		vector<int> order(n);
		for(int i = 0; i < n; i++) order[i] = i;
		bool isPossible = false;
		do {
			if(order[0] > 0) break;
			long long sum = 0;
			for(int i = 0; i < n; i++)
				if(i == n - 1) sum += cost[order[i]][0];
				else sum += cost[order[i]][order[i + 1]];
			if(sum == l) isPossible = true;
		} while(next_permutation(order.begin(), order.end()));

		printf("%s\n", isPossible ? "possible" : "impossible");
		return 0;
	}

	left = n / 2, right = n - left;
	bool isPossible = false;
	for(int leftLast = 1; leftLast < n; leftLast++) {
		for(int i = 0; i < (1 << n); i++) {
			if((i & 1) == 0) continue;
			if((i & (1 << leftLast)) == 0) continue;
			if(bits[i].size() != left) continue;

			vector<int> ord;
			for(int bit: bits[i])
				if(bit != 0 and bit != leftLast) ord.push_back(bit);

			calcRight((1 << n) - 1 - i, leftLast);

			do {
				long long cur = 0;
				if(ord.size() == 0) cur = cost[0][leftLast];
				else {
					cur = cost[ord.back()][leftLast] + cost[0][ord.front()];
					for(int i = 0; i < (int)ord.size() - 1; i++)
						cur += cost[ord[i]][ord[i + 1]];
				}

				if(rightCosts.count(l - cur) > 0) {
					isPossible = true;
					goto END;
				}
			} while(next_permutation(ord.begin(), ord.end()));
		}
	}

END:
	printf("%s\n", (isPossible ? "possible" : "impossible"));
	return 0;
}
