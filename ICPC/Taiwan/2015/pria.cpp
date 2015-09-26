#include <cstdio>

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i = 0; i <= m; i++) 
			if(i + (m - i) * 2 == n) {
				printf("%d %d\n", i, m - i);
				break;
			}
	}

	return 0;
}
