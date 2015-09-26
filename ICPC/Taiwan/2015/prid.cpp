#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

struct Frac {
	long long a, b;
	Frac() {}
	Frac(long long _a, long long _b) {
		if(_a == 0) {
			a = 0;
			b = 1;
		} else {
			long long v = __gcd(_a, _b);
			a = _a / v, b = _b / v;
		}
	}
	Frac(long long _a) {
		a = _a, b = 1;
	}
	void print() { printf("%lld/%lld\n", a, b); }

	Frac operator + (Frac arg) { return Frac(a * arg.b + b * arg.a, b * arg.b); }
	Frac operator - (Frac arg) { return Frac(a * arg.b - b * arg.a, b * arg.b); }
	Frac operator * (Frac arg) { return Frac(a * arg.a, b * arg.b); }
};

Frac dp[60][60];
bool isVisited[60][60];

Frac getAns(int red, int white) {
	Frac &ret = dp[red][white];
	if(isVisited[red][white]) return ret;
	isVisited[red][white] = true;

	if(white == 0) ret = Frac(1);
	else ret = Frac(red, (red + white)) + Frac(white, (red + white)) * (Frac(1) - getAns(red, white - 1));
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		long long a, b;
		scanf("%lld %lld", &a, &b);
		getAns(a, b).print();
	}

	return 0;
}
