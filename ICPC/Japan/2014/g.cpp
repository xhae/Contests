#include <string>
#include <algorithm>
#include <set>
#include <cstdio>
 
using namespace std;
 
int n, q;
string str;
 
const int base = (1 << 19);
int iTree[base << 1], delta[base << 1];
 
set<int> closes;
 
const int INF = (1 << 29);
 
void pushdown(int cs, int ce, int ind) {
    if(cs < ce and delta[ind] != 0) {
        iTree[ind] += delta[ind];
        if(ce - cs > 1) {
            delta[ind * 2] += delta[ind];
            delta[ind * 2 + 1] += delta[ind];
        }
        delta[ind] = 0;
    }
}
 
void update(int cs, int ce, int ts, int te, int ind, int d) {
    pushdown(cs, ce, ind);
 
    if(cs >= ce or ts >= te or cs >= te or ts >= ce) return;
    if(cs == ts and ce == te) {
        iTree[ind] += d;
        if(ce - cs > 1) {
            delta[ind * 2] += d;
            delta[ind * 2 + 1] += d;
        }
    } else if(ce - cs > 1) {
        int mid = (cs + ce) / 2;
        update(cs, mid, ts, min(te, mid), ind * 2, d);
        update(mid, ce, max(ts, mid), te, ind * 2 + 1, d);
        iTree[ind] = min(iTree[ind * 2], iTree[ind * 2 + 1]);
    }
}
 
int getMin(int cs, int ce, int ts, int te, int ind) {
    pushdown(cs, ce, ind);
    if(cs >= ce or ts >= te or cs >= te or ts >= ce) return INF;
    if(cs == ts and ce == te) return iTree[ind];
 
    int mid = (cs + ce) / 2;
    return min(getMin(cs, mid, ts, min(te, mid), ind * 2), getMin(mid, ce, max(ts, mid), te, ind * 2 + 1));
}
 
char temp[300001];
 
int main(void) {
    scanf("%d %d %s", &n, &q, temp);
    str = temp;
    for(int i = 0; i < n; i++)
        if(str[i] == '(') update(0, base, i, n, 1, 1);
        else {
            update(0, base, i, n, 1, -1);
            closes.insert(i);
        }
 
    while(q--) {
        int ind;
        scanf("%d", &ind);
        ind--;
        if(str[ind] == '(') {
            str[ind] = ')';
            closes.insert(ind);
            int first = *closes.begin();
            closes.erase(first);
            str[first] = '(';
            update(0, base, first, n, 1, 2);
            update(0, base, ind, n, 1, -2);
 
            printf("%d\n", first + 1);
        } else {
            closes.erase(ind);
            str[ind] = '(';
            update(0, base, ind, n, 1, 2);
 
            int s = 0, e = ind + 1, tar;
            while(s < e) {
                int mid = (s + e) / 2;
                int v = getMin(0, base, mid, ind + 1, 1);
                if(v >= 2) e = tar = mid;
                else s = mid + 1;
            }
 
            closes.insert(tar);
            str[tar] = ')';
            update(0, base, tar, n, 1, -2);
 
            printf("%d\n", tar + 1);
        }
    }
 
    return 0;
}
