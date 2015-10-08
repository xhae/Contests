#include <cstdio>

char str[101];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	int ans = 0;
	for(int i = 0; i < n; i++) {
		scanf("%s", str);
		int cnt = 0;
		for(int j = 0; j < m; j++) 
			if(str[j] == '.') {
				if(cnt % 2 == 1) ans += 2;
			} else {
				ans++;
				cnt++;
			}
	}

	printf("%d\n", ans / 2);

	return 0;
}
