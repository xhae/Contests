#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, l;
vector<pair<int, int>> list;
int arr[10010];
int res[10010];

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		scanf("%d %d %d",&n,&m,&l);
		for(int i=0;i<n;i++) arr[i]=i;
		list.resize(m);
		for(int i=0;i<m;i++) {
			scanf("%d %d", &list[i].second, &list[i].first);
		}
		sort(list.begin(), list.end());
		list.erase(unique(list.begin(), list.end()), list.end());
		for(auto &e: list) swap(arr[e.second], arr[e.second + 1]);
		for(int i=0;i<n;i++) {
			res[arr[i]]=i;
		}
		for(int i=0;i<n;i++)
			printf("%d\n",res[i]);
	}
}
