#include <cstdio>
#include <unordered_map>

using namespace std;

unordered_map<long long, int> cnt;

int n;
char str[300001];

int main(void) {
	scanf("%d %s", &n, str);
	long long ans = 0, stat = 0;
	cnt[0] = 1;
	for(int i = 0; i < n; i++) {
		char ch = str[i];
		if(ch <= 'Z') ch -= 'A';
		else ch = ch - 'a' + 26;

		long long nstat = stat ^ (1ll << ch);

		ans += cnt[nstat];
		for(int i = 0; i < 52; i++) {
			long long oddstat = nstat ^ (1ll << i);
			if(cnt.count(oddstat) > 0) ans += cnt[oddstat];
		}

		cnt[nstat]++;
		stat = nstat;
	}

	printf("%lld\n", ans);
	return 0;
}
