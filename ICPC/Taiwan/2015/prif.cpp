#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int n;
string str[3];
char temp[30001];

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < 3; i++) {
			scanf("%s", temp);
			str[i] = temp;
		}
		
		int base = 0, somesame[3] = {0, 0, 0}, alldiff = 0;
		for(int i = 0; i < n; i++) {
			if(str[0][i] == str[1][i] and str[1][i] == str[2][i]) base++;
			else if(str[0][i] == str[1][i]) somesame[0]++;
			else if(str[1][i] == str[2][i]) somesame[1]++;
			else if(str[0][i] == str[2][i]) somesame[2]++;
			else alldiff++;
		}

		int score[3] = {0, 0, 0};
		score[0] += somesame[0] + somesame[2];
		score[1] += somesame[0] + somesame[1];
		score[2] += somesame[1] + somesame[2];
		while(alldiff > 0) {
			int mv = min(score[0], min(score[1], score[2]));
			vector<int> mins;
			for(int i = 0; i < 3; i++) if(score[i] == mv) mins.push_back(i);
			if(mins.size() <= alldiff) {
				for(int ind: mins) score[ind]++;
				alldiff -= mins.size();
			} else break;
		}

		int mv = min(score[0], min(score[1], score[2]));
		vector<int> mins;
		for(int i = 0; i < 3; i++) if(score[i] == mv) mins.push_back(i);
		if(mins.size() == 1) {
			int ind = mins[0];
			int buf;
			if(ind == 0) buf = somesame[1];
			else if(ind == 1) buf = somesame[2];
			else buf = somesame[0];

			while(buf > 0) {
				bool isAble = true;
				for(int i = 0; i < 3; i++) {
					if(ind == i) continue;
					if(score[i] <= score[ind]) {
						isAble = false;
						break;
					}
				}

				if(isAble) {
					for(int i = 0; i < 3; i++)
						if(i == ind) score[i]++;
						else score[i]--;
				} else break;
			}
		}

		printf("%d\n", min(score[0], min(score[1], score[2])) + base);
	}

	return 0;
}

