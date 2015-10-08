#include <cstdio>

void print(int v, int len) {
	int arr[50];
	for(int i = 0; i < len; i++) {
		arr[i] = v % 2;
		v /= 2;
	}
	for(int i = len - 1; i >= 0; i--) printf("%d", arr[i]);
	printf("\n");
}

int main(void) {
	int m;
	scanf("%d", &m);
	int n = 1, len = 0;
	while(n < m) {
		len++;
		n *= 2;
	}

	int gap = n - m;
	int cur = 0, v = 0;
	for(int i = 0; i < m; i++) {
		if(gap > 0) print(v, len - 1);
		else print(v, len);

		gap--;
		v++;
		if(gap == 0) v *= 2;
	}
	
	return 0;
}
