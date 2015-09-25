#include <sstream>
#include <string>
#include <iostream>

using namespace std;

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		long long cur = 1;
		int n;
		scanf("%d", &n);
		bool over = false;
		while(n--) {
			long long v;
			scanf("%lld", &v);
			cur *= v;
			if(cur >= 10000) over = true;
			while(over and cur > 0 and cur % 10 == 0) cur /= 10;
			cur %= 10000;
		}

		printf("%04lld\n", cur);
	}

	return 0;
}
			
