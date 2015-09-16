#include <cstdio>

using namespace std;

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		long long n;
		scanf("%lld", &n);

		long long div, base;
		for(div = 2; ; div++) {
			long long adds = div * (div - 1) / 2;
			base = n - adds;
			if(base < div) {
				div = -1;
				break;
			}
			if(base % div == 0) {
				base /= div;
				break;
			}
		}

		if(div == -1) printf("IMPOSSIBLE\n");
		else {
			printf("%lld", n);
			for(long long i = 0; i < div; i++) {
				if(i == 0) printf(" = ");
				else printf(" + ");
				printf("%lld", base + i);
			}
			printf("\n");
		}
	}

	return 0;
}
