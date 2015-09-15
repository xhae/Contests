#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool notPrime[10000000];
int isUsed[10000000];

int main(void) {
	notPrime[0] = notPrime[1] = true;
	for(int i = 2; i <= 10000000; i++) {
		if(notPrime[i]) continue;
		for(int j = i * 2; j <= 10000000; j += i)
			notPrime[j] = true;
	}

	int T;
	cin >> T;
	for(int kase = 1; kase <= T; kase++) {
		string str;
		cin >> str;

		sort(str.begin(), str.end());
		int ans = 0;
		for(int i = 1; i < (1 << str.size()); i++) {
			vector<int> digits;
			for(int j = 0; j < str.size(); j++) if(i & (1 << j)) digits.push_back((int)(str[j] - '0'));
			do {
				int v = 0;
				for(int d: digits) v = v * 10 + d;
				if(!notPrime[v] and isUsed[v] != kase) {
					isUsed[v] = kase;
					ans++;
				}
			} while(next_permutation(digits.begin(), digits.end()));
		}

		cout << ans << "\n";
	}

	return 0;
}
