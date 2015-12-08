#include <cstdio>

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		char field[100][101];
		int r, c;
		bool cant[100][100][4] = {false, };

		char hash[200];
		hash['<'] = 0, hash['^'] = 1, hash['>'] = 2, hash['v'] = 3;

		scanf("%d %d", &r, &c);
		for(int i = 0; i < r; i++) scanf("%s", field[i]);
		int mov[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
		for(int i = 0; i < c; i++) {
			int cr = 0;
			while(cr < r and field[cr][i] == '.') cr++;
			if(cr < r) cant[cr][i][1] = true;
			cr = r - 1;
			while(cr >= 0 and field[cr][i] == '.') cr--;
			if(cr >= 0) cant[cr][i][3] = true;
		}
		for(int i = 0; i < r; i++) {
			int cc = 0;
			while(cc < c and field[i][cc] == '.') cc++;
			if(cc < c) cant[i][cc][0] = true;
			cc = c - 1;
			while(cc >= 0 and field[i][cc] == '.') cc--;
			if(cc >= 0) cant[i][cc][2] = true;
		}

		int ans = 0;
		for(int i = 0; i < r; i++)
			for(int j = 0; j < c; j++) {
				if(field[i][j] == '.') continue;
				if(cant[i][j][hash[field[i][j]]]) {
					bool hasValid = false;
					for(int k = 0; k < 4; k++)
						if(!cant[i][j][k]) {
							hasValid = true;
							break;
						}
					if(!hasValid) ans = -99999999;
					else ans++;
				}
			}
		if(ans < 0) ans = -1;
		printf("Case #%d: ", kase);
		if(ans == -1) printf("IMPOSSIBLE\n");
		else printf("%d\n", ans);
	}

	return 0;
}
