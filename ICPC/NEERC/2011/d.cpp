#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	vector<pair<char, int>> next;
	int getNext(char ch) {
		for(auto &e: next)
			if(e.first == ch)
				return e.second;
		return 0;
	}
} pre[400001], suf[400001];

int n;
string str[10000];

int pren, sufn;

void buildTrie(int &m, Node *node) {
	m = 1;
	for(int i = 0; i < n; i++) {
		int cur = 0;
		for(char ch: str[i]) {
			ch -= 'a';
			if(node[cur].getNext(ch) == 0) node[cur].next.push_back(make_pair(ch, m++));
			cur = node[cur].getNext(ch);
		}
	}
}

int main(void) {
	scanf("%d", &n);
	long long ans = 0;
	bool lengthOne[26] = {false, };
	for(int i = 0; i < n; i++) {
		char temp[41];
		scanf("%s", temp);
		str[i] = temp;
		if(str[i].size() == 1 and lengthOne[str[i][0] - 'a'] == false) {
			lengthOne[str[i][0] - 'a'] = true;
			ans++;
		}
	}

	bool isLast[26] = {false, };
	for(int i = 0; i < n; i++) isLast[str[i].back() - 'a'] = true;

	buildTrie(pren, pre);
	for(int i = 0; i < n; i++) reverse(str[i].begin(), str[i].end());
	buildTrie(sufn, suf);

	long long cnt[26] = {0, };
	for(int tar = 0; tar < sufn; tar++) {
		for(int j = 0; j < 26; j++)
			if(suf[tar].getNext(j) > 0)
				cnt[j]++;
	}

	for(int i = 1; i < pren; i++)
		for(int j = 0; j < 26; j++) {
			if(pre[i].getNext(j) == 0) ans += cnt[j];
			if(pre[i].getNext(j) > 0 and isLast[j]) ans++;
		}

	printf("%lld\n", ans);

	return 0;
}
