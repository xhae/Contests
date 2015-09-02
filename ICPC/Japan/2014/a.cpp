#include <cstdio>
#include <queue>
#include <algorithm>
 
using namespace std;
 
int dist[1 << 15];
 
void printBit(int cur, int n) {
    for(int i = n - 1; i >= 0; i--)
        printf("%d ", (cur & (1 << i)) > 0 ? 1 : 0);
}
 
int main(void) {
    int n, m, bits = 0, data[15];
    scanf("%d %d", &n, &m);
    if(n == 1) {
        printf("0\n");
        return 0;
    }
    for(int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        bits <<= 1;
        bits += v;
    }
    int goal[2] = {0, 0};
    for(int i = 0; i < m; i++) {
        scanf("%d", data + i);
        for(int j = 0; j < data[i]; j++) {
            goal[i % 2] <<= 1;
            goal[!(i % 2)] = (goal[!(i % 2)] * 2 + 1);
        }
    }
 
    fill(dist, dist + (1 << n), -1);
    dist[bits] = 0;
    queue<int> q;
    q.push(bits);
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
 
        for(int i = 0; i < n - 1; i++) {
            int upper = (((1 << 16) - 1) & cur) >> (i + 2);
            int lower = ((1 << i) - 1) & cur;
            int mid = (cur >> i) & 3;
            if(mid == 1) mid = 2;
            else if(mid == 2) mid = 1;
 
            int next = (((upper << 2) + mid) << i) + lower;
            if(dist[next] == -1) {
                dist[next] = dist[cur] + 1;
                q.push(next);
            }
        }
    }
 
    int ans = dist[goal[0]];
    if(ans == -1 or (dist[goal[1]] != -1 and ans > dist[goal[1]])) ans = dist[goal[1]];
    printf("%d\n", ans);
    return 0;
}
