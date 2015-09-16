#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int n;
vector<vector<int>> type2, type3;

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		int m[3];
		scanf("%d %d %d %d", &n, m, m + 1, m + 2);
		type2.clear();
		type3.clear();

		bool mustTrue[1500] = {false, };
		for(int i = 0; i < m[0]; i++) {
			int v;
			scanf("%d", &v);
			mustTrue[v - 1] = true;
		}

		for(int i = 0; i < m[1]; i++) {
			int curn;
			scanf("%d", &curn);
			vector<int> list(curn);
			for(int j = 0; j < curn; j++) {
				scanf("%d", &list[j]);
				list[j]--;
			}
			type2.push_back(list);
		}

		for(int i = 0; i < m[2]; i++) {
			int curn;
			scanf("%d", &curn);
			vector<int> list(curn + 1);
			for(int j = 0; j <= curn; j++) {
				scanf("%d", &list[j]);
				list[j]--;
			}
			type3.push_back(list);
		}
		
		while(true) {
			bool changed = false;
			for(auto &list: type3) {
				if(mustTrue[list.back()]) continue;
				bool allTrue = true;
				for(int j = 0; j < list.size() - 1; j++)
					if(!mustTrue[list[j]]) {
						allTrue = false;
						break;
					}
				if(allTrue) {
					mustTrue[list.back()] = true;
					changed = true;
				}
			}

			if(!changed) break;
		}

		bool isValid = true;
		for(auto &list: type2) {
			bool haveFalse = false;
			for(int ind: list)
				if(!mustTrue[ind]) {
					haveFalse = true;
					break;
				}
			if(!haveFalse) {
				isValid = false;
				break;
			}
		}

		printf("%s\n", isValid ? "YES" : "NO");
	}

	return 0;
}
