#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		int a, b;
		scanf("%d %d", &a, &b);

		if(b == 0) b = a;
		int v = __gcd(a, b);
		int ans = a / v;
		if(ans == a) printf("Yes\n");
		else printf("No %d\n", ans);
	}

	return 0;
}

