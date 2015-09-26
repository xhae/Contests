#include <cstdio>
#include <string>

using namespace std;

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		string str;
		for(char ch = 'a'; ch <= 'z'; ch++) str += ch;
		while(n--) {
			int v;
			scanf("%d", &v);
			printf("%c", str[v]);
			str = str[v] + str.substr(0, v) + str.substr(v + 1);
		}
		printf("\n");
	}

	return 0;
}

