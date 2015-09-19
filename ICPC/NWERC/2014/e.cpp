#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

double log2(double v) {
	return log(v) / log(2);
}

double n, p, s, v;

double func(double c) {
	return n * pow(log2(n), sqrt(2) * c) / 1e9 / p + (1 + 1 / c) * s / v;
}


int main(void) {
	scanf("%lf %lf %lf %lf", &n, &p, &s, &v);
	double s = 0, e = 50;
	for(int lv = 0; lv < 100; lv++) {
		double m1 = (s * 2 + e) / 3;
		double m2 = (s + e * 2) / 3;
		double v1 = func(m1);
		double v2 = func(m2);
		if(v1 < v2) e = m2;
		else s = m1;
	}

	printf("%.10lf %.10lf\n", func(s), s);
	return 0;
}
