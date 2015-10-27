#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> pieces[16];
int n, w, h;

string field[20];

bool tryFill(int y, int x, int ind, bool toFill) {
	int gy = -99999999, gx;
	for(int i = 0; i < pieces[ind].size() and gy == -99999999; i++)
		for(int j = 0; j < pieces[ind][i].size(); j++)
			if(pieces[ind][i][j] != '.') {
				gy = y - i;
				gx = x - j;
				break;
			}

	if(toFill) {
		for(int i = 0; i < pieces[ind].size(); i++)
			for(int j = 0; j < pieces[ind][i].size(); j++) {
				int ty = i + gy, tx = j + gx;
				if(ty < 0 or ty >= n * h or tx < 0 or tx >= n * w) continue;
				if(pieces[ind][i][j] != '.' and field[ty][tx] != 0)
					return false;
			}
		for(int i = 0; i < pieces[ind].size(); i++)
			for(int j = 0; j < pieces[ind][i].size(); j++) {
				int ty = i + gy, tx = j + gx;
				if(ty < 0 or ty >= n * h or tx < 0 or tx >= n * w) continue;
				if(pieces[ind][i][j] != '.') field[ty][tx] = ind + 'A';
			}
	} else {
		for(int i = 0; i < pieces[ind].size(); i++)
			for(int j = 0; j < pieces[ind][i].size(); j++) {
				int ty = i + gy, tx = j + gx;
				if(ty < 0 or ty >= n * h or tx < 0 or tx >= n * w) continue;
				if(pieces[ind][i][j] != '.') field[ty][tx] = 0;
			}
	}
	return true;
}

bool backtr(int nth, int used) {
	if(nth == n * n) return true;

	int y = -1, x;
	for(int i = 0; i < n * h and y == -1; i++)
		for(int j = 0; j < n * w; j++)
			if(field[i][j] == 0) {
				y = i;
				x = j;
				break;
			}

	for(int i = 0; i < n * n; i++) {
		if(used & (1 << i)) continue;

		char ch = i + 'A';
		bool filled = tryFill(y, x, i, true);
		if(!filled) continue;

		int sx, sy = -1, ex, ey;
		for(int y = 0; y < n * h && sy == -1; y++)
			for(int x = 0; x < n * w; x++)
				if(field[y][x] == i + 'A' and y % h == 0 and x % w == 0) {
					sy = y, sx = x;
					ey = sy + h - 1, ex = sx + w - 1;
					break;
				}
		if(sy == -1) {
			tryFill(y, x, i, false);
			continue;
		}

		bool isValid = true;
		if(field[sy][sx] != ch or field[ey][sx] != ch or field[sy][ex] != ch or field[ey][ex] != ch)
			isValid = false;
		if(isValid and sy - 1 > 0) {
			bool haveHole = false;
			for(int j = 0; j < w; j++)
				if(field[sy][sx + j] != ch or field[sy - 1][sx + j] == ch)
					haveHole = true;
			if(!haveHole) isValid = false;
		}
		if(isValid and sx - 1 > 0) {
			bool haveHole = false;
			for(int j = 0; j < h; j++)
				if(field[sy + j][sx] != ch or field[sy + j][sx - 1] == ch)
					haveHole = true;
			if(!haveHole) isValid = false;
		}
		if(isValid and ey + 1 < n * h) {
			bool haveHole = false;
			for(int j = 0; j < w; j++)
				if(field[ey][sx + j] != ch or field[ey + 1][sx + j] == ch)
					haveHole = true;
			if(!haveHole) isValid = false;
		}
		if(isValid and ex + 1 < n * w) {
			bool haveHole = false;
			for(int j = 0; j < h; j++)
				if(field[sy + j][ex] != ch or field[sy + j][ex + 1] == ch)
					haveHole = true;
			if(!haveHole) isValid = false;
		}

		if(isValid) {
			if(backtr(nth + 1, used | (1 << i)))
				return true;
		}

		tryFill(y, x, i, false);
	}

	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n >> w >> h;
	for(int nn = 1; ; nn++)
		if(nn * nn == n) {
			n = nn;
			break;
		}
	for(int i = 0; i < n * n; i++) {
		pieces[i].resize(3 * h - 2);
		for(int j = 0; j < pieces[i].size(); j++)
			cin >> pieces[i][j];
	}

	for(int i = 0; i < n * h; i++) field[i] = string(n * w, 0);
	backtr(0, 0);

	cout << n * w << " " << n * h << "\n";
	for(int i = 0; i < n * h; i++) cout << field[i] << "\n";
	return 0;
}
