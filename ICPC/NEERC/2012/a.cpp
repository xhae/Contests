#include <cstdio>

int h, w, c, cnt[9];
char next() {
	for(int i = 0; i < 10; i++)
		if(cnt[i] > 0) {
			cnt[i]--;
			return (i + '1');
		}
	return 0;
}

int main(void) {
	scanf("%d %d %d", &h, &w, &c);
	for(int i = 0; i < c; i++) scanf("%d", cnt + i);
	char ans[10][11];
	for(int i = 0; i < h; i++) {
		if(i % 2 == 0)
			for(int j = 0; j < w; j++)
				ans[i][j] = next();
		else
			for(int j = w - 1; j >= 0; j--)
				ans[i][j] = next();

		ans[i][w] = 0;
	}

	for(int i = 0; i < h; i++) printf("%s\n", ans[i]);
	return 0;
}
