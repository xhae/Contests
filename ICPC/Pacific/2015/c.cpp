#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int n;
pair<vector<int>, string> data[1000];

bool sortf(const pair<vector<int>, string> &a, const pair<vector<int>, string> &b) {
	for(int i = 0; i < max(a.first.size(), b.first.size()); i++) {
		int v1 = i < a.first.size() ? a.first[i] : 1;
		int v2 = i < b.first.size() ? b.first[i] : 1;
		if(v1 < v2) return true;
		else if(v1 > v2) return false;
	}
	return a.second < b.second;
}

int main(void) {
	cin >> n;
	string temp;
	getline(cin, temp);
	for(int i = 0; i < n; i++) {
		getline(cin, temp);
		stringstream it(temp);
		vector<string> strs;
		string str;
		while(it >> str) strs.push_back(str);
		strs.pop_back();
		data[i].second = strs[0].substr(0, strs[0].size() - 1);
		for(int j = strs.size() - 1; j > 0; j--) {
			if(strs[j] == "upper") data[i].first.push_back(0);
			else if(strs[j] == "middle") data[i].first.push_back(1);
			else data[i].first.push_back(2);
		}
	}

	sort(data, data + n, sortf);
	for(int i = 0; i < n; i++) cout << data[i].second << "\n";

	return 0;
}
