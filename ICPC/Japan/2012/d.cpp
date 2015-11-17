#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

int n;
double data[8];

const double EPS = 1e-3;
bool EQ(double a, double b) { return abs(a - b) < EPS; }

vector<double> gauss(vector<vector<double>> &tar) {
	vector<double> ret;

	for(int i = 0; i <= n; i++) {
		int ind = -1;
		double maxV;
		for(int j = i; j <= n; j++) 
			if(!EQ(tar[j][i], 0)) { 
				if(ind == -1 or maxV < abs(tar[j][i])) {
					ind = j;
					maxV = abs(tar[j][i]);
				}
			}
		if(ind == -1) {
			return ret;
		}

		if(i != ind) swap(tar[i], tar[ind]);

		double base = tar[i][i];
		for(auto &v: tar[i]) v /= base;

		for(int j = 0; j <= n; j++) {
			if(i == j) continue;
			double c = tar[j][i];
			for(int k = 0; k <= n + 1; k++) tar[j][k] -= tar[i][k] * c;
		}
	}

	for(int i = 0; i <= n; i++) ret.push_back(tar[i].back());
	return ret;
}

int main(void) {
	while(scanf("%d", &n), n > 0) {
		for(int i = 0; i < n + 3; i++) scanf("%lf", data + i);
		vector<double> terms[8];
		for(int i = 0; i < n + 3; i++) {
			double cur = 1;
			for(int j = 0; j <= n; j++) {
				terms[i].push_back(cur);
				cur *= i;
			}
			terms[i].push_back(data[i]);
		}

		int ans = -1;
		for(int cand = 0; cand < n + 3; cand++) {
			vector<vector<double>> reses;
			vector<vector<double>> mat;
			bool isValid = true;

			for(int skip = 0; skip < n + 3; skip++) {
				if(skip == cand) continue;
				mat.clear();
				for(int i = 0; i < n + 3; i++) 
					if(i == cand or i == skip) continue;
					else mat.push_back(terms[i]);
				auto res = gauss(mat);
				if(res.size() == 0) {
					isValid = false;
					break;
				}
				reses.push_back(res);
			}

			if(!isValid) continue;

			for(int i = 1; i < reses.size() and isValid; i++)
				for(int j = 0; j < reses[0].size() and isValid; j++)
					if(!EQ(reses[0][j], reses[i][j]))
						isValid = false;

			if(isValid) {
				ans = cand;
				break;
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}
