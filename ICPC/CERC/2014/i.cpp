#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

long long n, data[100000];
vector<pair<long long, char>> bricks;

int main(void) {
	long long T;
	scanf("%lld", &T);
	while(T--) {
		scanf("%lld", &n);
		long long sum[2] = {0, 0};
		char type[2], last = 'A';

		bricks.clear();

		long long cur = 0;
		for(int i = 0; i < n; i++) {
			long long v;
			scanf("%lld %s", &v, type);
			if(type[0] == 'W') sum[0] += v;
			else sum[1] += v;

			if(type[0] == last)	cur += v;
			else {
				if(cur > 0) bricks.push_back(make_pair(cur, last));
				cur = v;
				last = type[0];
			}
		}

		bricks.push_back(make_pair(cur, last));

		if(bricks.size() == 1) {
			printf("%lld\n", bricks[0].first);
			continue;
		}

		long long gcdv = __gcd(sum[0], sum[1]);
		sum[0] /= gcdv, sum[1] /= gcdv;

		long long white = 0, black = 0, ans = 0;
		for(auto &b: bricks) {
			if(white == 0 and black == 0) {
				if(b.second == 'W') white = b.first;
				else black = b.first;
			} else {
				if(b.second == 'W') {
					if(black % sum[1] == 0) {
						long long reqWhite = black / sum[1] * sum[0];
						if(white < reqWhite and white + b.first >= reqWhite) ans++;
						white += b.first;
					} else white += b.first;
				} else {
					if(white % sum[0] == 0) {
						long long reqBlack = white / sum[0] * sum[1];
						if(black < reqBlack and black + b.first >= reqBlack) ans++;
						black += b.first;
					} else black += b.first;
				}
			}
		}

		printf("%lld\n", ans);
	}

	return 0;
}
