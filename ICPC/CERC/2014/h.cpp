#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
 
using namespace std;
 
vector<int> cands;
 
int board[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {-1, 0, -1}};
 
void backtr(int y, int x, int cur) {
    if(cur >= 1000) return;
    if(y >= 4 or x >= 3) return;
    int v = board[y][x];
    if(v == -1) return;
 
    int next = cur * 10 + v;
    cands.push_back(next);
    if(cur != next) backtr(y, x, next);
    backtr(y + 1, x, cur);
    backtr(y, x + 1, cur);
}
 
int main(void) {
    cands.push_back(0);
    backtr(0, 0, 0);
    sort(cands.begin(), cands.end());
 
    int T;
    scanf("%d", &T);
    while(T--) {
        int K;
        scanf("%d", &K);
        if(*lower_bound(cands.begin(), cands.end(), K) == K) printf("%d\n", K);
        else {
            int lower = *(lower_bound(cands.begin(), cands.end(), K) - 1);
            int upper = *upper_bound(cands.begin(), cands.end(), K);
 
            if(K - lower < upper - K) printf("%d\n", lower);
            else printf("%d\n", upper);
        }
    }
 
    return 0;
}
