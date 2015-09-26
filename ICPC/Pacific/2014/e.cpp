#include <iostream>
#include <string>
#include <cstring>

using namespace std;

bool isHill(string arg) {
	bool isDown = false;
	for(int i = 1; i < arg.size(); i++) {
		if(arg[i] > arg[i - 1] and isDown) return false;
		if(arg[i] < arg[i - 1]) isDown = true;
	}
	return true;
}

long long dp[70][3][2][10];
string str;

long long getAns(int nth, int stat, int isDown, int last) { // 0 for eq, 1 for gt, 2 for less
	long long &ret = dp[nth][stat][isDown][last];
	if(ret != -1) return ret;

	if(nth == str.size() - 1) {
		if(stat == 1) ret = 0;
		else if(stat == 0) ret = str[nth] + 1;
		else if(isDown == false) ret = 10;
		else ret = last + 1;
	} else {
		ret = 0;
		for(int i = 0; i < 10; i++) {
			if(isDown && i > last) break;
			if(stat == 0) {
				int nstat = 0;
				if(i > str[nth]) nstat = 1;
				if(i < str[nth]) nstat = 2;
				ret += 1 + getAns(nth + 1, nstat, isDown ? isDown : last > i, i);
			} else if(stat == 1) {
				ret += 1 + getAns(nth + 1, 1, isDown ? isDown : last > i, i);
			} else {
				ret += 1 + getAns(nth + 1, 2, isDown ? isDown : last > i, i);
			}
		}
	}

	return ret;
}

int main(void) {
	int T;
	cin >> T;
	while(T--) {
		cin >> str;
		if(!isHill(str)) {
			cout << "-1\n";
			continue;
		}

		for(char &ch: str) ch -= '0';

		if(str.size() == 1) cout << (int)str[0] << "\n";
		else {
			memset(dp, -1, sizeof(dp));
			long long ans = 0;
			for(int i = 1; i <= 9; i++) ans += 1 + getAns(1, i > str[0] ? 1 : (i == str[0] ? 0 : 2), 0, i);
			cout << ans << "\n";
		}
	}

	return 0;
}
