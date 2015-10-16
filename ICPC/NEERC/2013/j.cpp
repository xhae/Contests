#include <cstdio>
#include <string>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

char temp[1000];
map<string, int> latest;
int dp[50000][2];

int main(void) {
	int n;
	scanf("%d", &n);
	gets(temp);

	int anslen = 0, ansind;

	for(int i = 0; i < n; i++) {
		gets(temp);
		string str = temp;
		stringstream it(str);
		string handle;
		it >> handle;
		handle.pop_back();

		dp[i][0] = 1;
		dp[i][1] = -1;
		if(anslen == 0) {
			anslen = 1;
			ansind = i;
		}
	
		string word;
		while(it >> word) {
			if(word[0] == '@') {
				if(handle == word) continue;
				if(latest.count(word) == 0) continue;

				int lastind = latest[word];

				if(dp[lastind][0] + 1 > dp[i][0]) {
					dp[i][0] = dp[lastind][0] + 1;
					dp[i][1] = lastind;

					if(anslen < dp[i][0]) {
						anslen = dp[i][0];
						ansind = i;
					}
				}
			}
		}

		if(latest.count(handle) == 0 or dp[latest[handle]][0] < dp[i][0]) latest[handle] = i;
	}

	printf("%d\n", anslen);
	if(anslen == 1) printf("1\n");
	else {
		vector<int> ans;
		int cur = ansind;
		while(ansind != -1) {
			ans.push_back(ansind);
			ansind = dp[ansind][1];
		}
		for(int i = ans.size() - 1; i >= 0; i--) printf("%d ", ans[i] + 1);
	}

	return 0;
}
