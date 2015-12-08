#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;

int main(void) {
	int T;
	cin >> T;
	for(int kase = 1; kase <= T; kase++) {
		int n;
		long double v, x;
		cin >> n >> v >> x;
		vector<pair<long double, long double>> data(n);
		for(int i = 0; i < n; i++) cin >> data[i].second >> data[i].first;
		sort(data.begin(), data.end());

		long double s = 0, e = 1e8;
		bool isValid = false;
		for(int lv = 0; lv < 200; lv++) {
			long double mid = (s + e) / 2;
			long double curv = 0, curvx = 0;
			for(int i = 0; i < n; i++) {
				long double curMax = data[i].second * mid;
				if(v - curv > curMax) {
					curv += curMax;
					curvx += curMax * data[i].first;
				} else {
					curvx += (v - curv) * data[i].first;
					curv = v;
					break;
				}
			}

			if(curv != v) {
				s = mid;
				continue;
			}

			if(curvx > v * x) {
				s = mid;
				continue;
			}

			curv = 0, curvx = 0;
			for(int i = n - 1; i >= 0; i--) {
				long double curMax = data[i].second * mid;
				if(v - curv > curMax) {
					curv += curMax;
					curvx += curMax * data[i].first;
				} else {
					curvx += (v - curv) * data[i].first;
					curv = v;
					break;
				}
			}

			if(curvx < v * x) {
				s = mid;
				continue;
			}

			isValid = true;
			e = mid;
		}

		cout << "Case #" << kase << ": ";
		if(!isValid) cout << "IMPOSSIBLE\n";
		else printf("%.9Lf\n", s);
	}

	return 0;
}
