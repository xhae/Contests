#include <cstdio>
#include <numeric>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const double EPS = 1e-9;
bool EQ(double a, double b) { return abs(a - b) < EPS; }

int main(void) {
	int T;
	scanf("%d", &T);
	int tot = 0;
	while(T--) {
		vector<double> lens(3);
		double weight;
		for(int i = 0; i < 3; i++) scanf("%lf", &lens[i]);
		scanf("%lf", &weight);

		bool isAble = false;
		double sum = accumulate(lens.begin(), lens.end(), 0.0);
		if((EQ(weight, 7) or weight < 7)) {
			sort(lens.begin(), lens.end());
			if(sum <= 125 or ((EQ(lens[0], 25) or lens[0] < 25) and 
				(EQ(lens[1], 45) or lens[1] < 45) and 
				(EQ(lens[2], 56) or lens[2] < 56))) isAble = true;
		}

		printf("%d\n", (int)isAble);
		tot += isAble;
	}

	printf("%d\n", tot);
	return 0;
}
