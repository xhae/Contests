#include <cstdio>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;

int n;
double s;
vector<tuple<double, double, string>> data;

const double PI = acos(-1.0);

vector<string> hilSort(double l, const vector<tuple<double, double, string>> &arr) {
	vector<string> ret;
	if(arr.size() == 0) return ret;
	else if(arr.size() == 1) {
		ret.push_back(get<2>(arr[0]));
		return ret;
	} else {
		double half = l / 2;
		vector<tuple<double, double, string>> next[4];
		for(auto e: arr) {
			double x, y;
			tie(x, y, ignore) = e;
			if(x < half and y < half) next[0].push_back(e);
			else if(x < half and y > half) {
				get<1>(e) -= half;
				next[1].push_back(e);
			} else if(x > half and y > half) {
				get<0>(e) -= half;
				get<1>(e) -= half;
				next[2].push_back(e);
			} else {
				get<0>(e) -= half;
				next[3].push_back(e);
			}
		}
		for(auto &e: next[0]) {
			double x, y;
			tie(x, y, ignore) = e;
			swap(get<0>(e), get<1>(e));
		}
		for(auto &e: next[3]) {
			double x, y;
			tie(x, y, ignore) = e;
			double a = (half - x - y) / 2;
			get<0>(e) = x + a * 2;
			get<1>(e) = y + a * 2;
		}

		for(int i = 0; i < 4; i++) {
			auto res = hilSort(half, next[i]);
			for(auto s: res) ret.push_back(s);
		}
		return ret;
	}
}

int main(void) {
	scanf("%d %lf", &n, &s);
	data.resize(n);
	for(int i = 0; i < n; i++) {
		char temp[50];
		double x, y;
		scanf("%lf %lf %s", &x, &y, temp);
		data[i] = make_tuple(x, y, temp);
	}

	vector<string> ans = hilSort(s, data);
	for(int i = 0; i < ans.size(); i++)
		printf("%s\n", ans[i].c_str());

	return 0;
}
