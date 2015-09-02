#include <cstdio>
#include <algorithm>
 
using namespace std;
 
int n, m;
int required[1001];
 
int main(void) {
    int last = 0;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        required[u] = max(required[u], v);
    }
 
    int ans = 0, s = 0, e = 0;
    for(int i = 1; i <= n; i++) {
        if(required[i] > 0) {
            if(s == 0) {
                s = i;
                e = required[i];
            } else if(i > e) {
                ans += (e - last + e - s);
                last = s;
                s = i;
                e = required[i];
            } else e = max(e, required[i]);
        }
    }
 
    if(s > 0) {
        ans += (e - last + e - s);
        last = s;
    }
    ans += (n + 1 - last);
    printf("%d\n", ans);
 
    return 0;
}
