#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <random>
 
using namespace std;
 
long long n, p;

struct MT19937 {
    private:
        static std::mt19937_64 rng;
    public:
        // This is equivalent to srand().
        static void seed(uint64_t new_seed = std::mt19937_64::default_seed) {
            rng.seed(new_seed);
        }
 
        // This is equivalent to rand().
        static uint64_t get() {
            return rng();
        }
};
 
std::mt19937_64 MT19937::rng;

const double EPS = 1e-9;
bool EQ(double a, double b) { return abs(a - b) < EPS; }

struct Point {
	long long x, y;
	Point operator - (Point a) const { return Point{x - a.x, y - a.y}; }
} coord[100000];

long long ccw(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}
 
int main(void) {
    MT19937::seed();
    scanf("%lld %lld", &n, &p);
    long long req = (n * p + 99) / 100;

    if(n == 1) {
    	printf("possible\n");
    	return 0;
	}

    for(int i = 0; i < n; i++) scanf("%lld %lld", &coord[i].x, &coord[i].y);
 
 
    for(int i = 0; i < 170; i++) {
        int i1 = MT19937::get() % n;
        int i2;
        while(i2 = MT19937::get() % n, i2 == i1);        
 
 		Point gap = coord[i2] - coord[i1];
 
        int cnt = 2;
        for(int j = 0; j < n; j++) {
            if(j == i1 or j == i2) continue;
            Point curGap = coord[j] - coord[i1];
            if(ccw(gap, curGap) == 0) {
                cnt++;
                if(cnt >= req) break;
            }
        }
		if(cnt >= req) {
			printf("possible\n");
			return 0;
		}
    }
 
    printf("impossible\n");
    return 0;
}
