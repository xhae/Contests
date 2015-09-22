#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

long long H, h, m, s;
struct Frac {
	long long a, b;
	Frac(){}
	Frac(long long _a, long long _b) {
		if(_a == 0) a = 0, b = 1;
		else {
			long long v = __gcd(_a, _b);
			a = _a / v, b = _b / v;
		}
	}
	Frac operator + (Frac arg) { return Frac(a * arg.b + b * arg.a, b * arg.b); }
	Frac operator - (Frac arg) { return Frac(a * arg.b - b * arg.a, b * arg.b); }
	Frac operator * (Frac arg) { return Frac(a * arg.a, b * arg.b); }
	bool operator < (Frac arg) const { return a * arg.b < b * arg.a; };
	bool operator == (Frac arg) { return a == arg.a and b == arg.b; }
	Frac rev() { return Frac(b, a); }

	void print() { printf("%lld / %lld, %lf\n", a, b, a / (double)b); }
};

void setSec(Frac tarSec, Frac &hour, Frac &min, Frac &sec) {
	hour = tarSec * Frac(1, H * 3600);
	min = tarSec * Frac(1, 3600);
	sec = tarSec * Frac(1, 60);

	while(Frac(1, 1) == hour or Frac(1, 1) < hour) hour = hour - Frac(1, 1);
	while(Frac(1, 1) == min or Frac(1, 1) < min) min = min - Frac(1, 1);
	while(Frac(1, 1) == sec or Frac(1, 1) < sec) sec = sec - Frac(1, 1);
}

Frac based(Frac base, Frac tar) {
	Frac unit(1, 1);
	tar = tar + unit - base;
	if(tar == unit or unit < tar) tar = tar - unit;
	return tar;
}

int main(void) {
	while(scanf("%lld %lld %lld %lld", &H, &h, &m, &s), H > 0) {
		Frac hour, min, sec, curSec;
		while(true) {
			curSec = Frac(h * 3600 + m * 60 + s, 1);
			setSec(curSec, hour, min, sec);

			if(hour == min or hour == sec or min == sec) {
				s++;
				if(s == 60) {
					s = 0;
					m++;
				}
				if(m == 60) {
					m = 0;
					h++;
				}
				if(h == H) h = 0;
			} else break;
		}

AGAIN:
		Frac unit(1, 1);
		Frac nmin = based(sec, min), nhour = based(sec, hour);

		if(nmin < nhour) {
			Frac nsec = based(hour, sec);
			nmin = based(hour, min);

			if(nsec * Frac(2, 1) < nmin) {
				Frac l1 = nmin;
				Frac v1(1, 60 * 60);
				Frac l2(0, 1);
				Frac v2(1, 60 * H * 60);
				Frac l3 = nsec;
				Frac v3 = Frac(1, 60);

				Frac t = (l1 - l3 - l3 + l2) * ((v3 - v2 - v1 + v3).rev());
				curSec = curSec + t;
			} else if(nmin < nsec * Frac(2, 1)) {
				Frac l1 = nmin;
				Frac v1(1, 60 * 60);
				Frac l2(1, 1);
				Frac v2(1, 60 * H * 60);
				Frac l3 = nsec;
				Frac v3 = Frac(1, 60);

				Frac t = (l1 - l3 - l3 + l2) * ((v3 - v2 - v1 + v3).rev());
				curSec = curSec + t;
			}
		} else {
			Frac nsec = based(min, sec);
			nhour = based(min, hour);

			if(nsec * Frac(2, 1) < nhour) {
				Frac l1 = nhour;
				Frac v1(1, 60 * 60 * H);
				Frac l2(0, 1);
				Frac v2(1, 60 * 60);
				Frac l3 = nsec;
				Frac v3 = Frac(1, 60);

				Frac t = (l1 - l3 - l3 + l2) * ((v3 - v2 - v1 + v3).rev());
				curSec = curSec + t;
			} else if(nhour < nsec * Frac(2, 1)) {
				Frac l1 = nhour;
				Frac v1(1, 60 * 60 * H);
				Frac l2(1, 1);
				Frac v2(1, 60 * 60);
				Frac l3 = nsec;
				Frac v3 = Frac(1, 60);

				Frac t = (l1 - l3 - l3 + l2) * ((v3 - v2 - v1 + v3).rev());
				curSec = curSec + t;
			}
		}

		{
			Frac nhour, nmin, nsec;
			setSec(curSec, nhour, nmin, nsec);
			if(nhour == nmin or nhour == nsec or nmin == nsec) {
				curSec = curSec + Frac(1, curSec.b * 2);
				setSec(curSec, hour, min, sec);
				goto AGAIN;
			}
		}

		Frac aday(60 * 60 * H, 1);
		Frac ahour(60 * 60, 1);
		Frac amin(60, 1);

		while(aday == curSec or aday < curSec) curSec = curSec - aday;
		int ans[2] = {0, 0};
		while(ahour == curSec or ahour < curSec) {
			ans[0]++;
			curSec = curSec - ahour;
		}
		while(amin == curSec or amin < curSec) {
			curSec = curSec - amin;
			ans[1]++;
		}


		printf("%d %d %lld %lld\n", ans[0], ans[1], curSec.a, curSec.b);
	}

	return 0;
}
