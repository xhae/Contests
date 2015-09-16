#include <cstdio>

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n, arr[1000];
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d", arr + i);
			arr[i]--;
		}

		int ans = 0;
		for(int i = 0; i < n; i++) {
			if(arr[i] == -1) continue;
			ans++;
			int ind = i;
			while(arr[ind] != -1) {
				int nind = arr[ind];
				arr[ind] = -1;
				ind = nind;
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}
