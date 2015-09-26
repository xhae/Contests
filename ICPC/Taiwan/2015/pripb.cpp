#include <cstdio>

using namespace std;

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		long long cur = 1, divided = 1;
		int n;
		scanf("%d", &n);
		bool over = false;
		int cnt[2] = {0, 0};
		while(n--) {
			long long v;
			scanf("%lld", &v);
			cur *= v;
			if(cur >= 10000) over = true;

			while(v > 0 and v % 2 == 0) {
				v /= 2;
				cnt[0]++;
			}
			while(v > 0 and v % 5 == 0) {
				v /= 5;
				cnt[1]++;
			}

			divided *= v;
			divided %= 10000;
		}

		if(!over) printf("%04lld\n", cur);
		else {
			if(cnt[0] > cnt[1]) {
				cnt[0] -= cnt[1];
				cnt[1] = 0;
			} else {
				cnt[1] -= cnt[0];
				cnt[0] = 0;
			}

			while(cnt[0]--) divided = divided * 2 % 10000;
			while(cnt[1]--) divided = divided * 5 % 10000;

			printf("%04lld\n", divided);
		}
	}

	return 0;
}
			
