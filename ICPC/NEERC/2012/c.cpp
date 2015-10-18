#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

pair<int, int> data[100000];
int n;

int main(void) {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d %d", &data[i].first, &data[i].second);
	sort(data, data + n);

	double ans = 99999999;
	for(int si = 0; si < n; ) {
		int curEnd = data[si].second;
		int ei = si + 1;
		while(ei < n and data[ei].first < curEnd) {
			curEnd = data[ei].second;
			ei++;
		}

		double s = 0, e = 99999999;
		for(int lv = 0; lv < 60; lv++) {
			double mid = (s + e) / 2;
			
			double current = 0;
			bool isAble = true;
			for(int i = si; i < ei; i++) {
				if(current < data[i].first) current = data[i].first;
				if(current + mid > data[i].second) {
					isAble = false;
					break;
				}
				current += mid;
			}

			if(isAble) s = mid;
			else e = mid;
		}

		ans = min(ans, s);
		si = ei;
	}

	double gap = 999999999;

	long long ians[2];

	for(int base = 1; base <= n; base++) {
		long long upper = round(ans * base) + 1e-9;
		double curGap = abs(ans - upper / (double)base);
		if(curGap < gap) {
			gap = curGap;
			ians[0] = upper, ians[1] = base;
		}
	}

	long long gcdv = __gcd(ians[0], ians[1]);
	ians[0] /= gcdv, ians[1] /= gcdv;
	printf("%lld/%lld\n", ians[0], ians[1]);

	return 0;
}
