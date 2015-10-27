#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);

	string base;
	cin >> base;
	int n;
	cin >> n;

	vector<string> ans;
	while(n--) {
		string cur;
		cin >> cur;
		bool isAble = true;
		for(int i = 0; i < 9; i++) 
			if(base[i] != '*' and base[i] != cur[i]) {
				isAble = false;
				break;
			}
		if(isAble) ans.push_back(cur);
	}

	cout << ans.size() << "\n";
	for(auto &s: ans) cout << s << "\n";
	return 0;
}
