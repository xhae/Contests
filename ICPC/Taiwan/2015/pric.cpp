#include <string>
#include <cstring>
#include <iostream>

using namespace std;

string orig, pat;
int dp[10001];

int getAns(int ind) {
	int &ret = dp[ind];
	if(ret != -1) return ret;

	if(ind == orig.size()) ret = 0;
	else {
		ret = getAns(ind + 1) + 1;
		if(orig.size() - ind >= pat.size()) {
			bool isMatch = true;
			for(int i = 0; i < pat.size(); i++)
				if(pat[i] != orig[ind + i]) {
					isMatch = false;
					break;
				}
			if(isMatch) ret = min(ret, getAns(ind + pat.size()) + 1);
		}
	}

	return ret;
}

int main(void) {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) {
		cin >> orig >> pat;
		memset(dp, -1, sizeof(dp));
		cout << getAns(0) << "\n";
	}

	return 0;
}
