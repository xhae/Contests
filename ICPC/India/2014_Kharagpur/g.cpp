#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

struct Node {
	int city, hour, energy;
	bool operator < (const Node &a) const {
		if(city != a.city) return city < a.city;
		if(hour != a.hour) return hour < a.hour;
		return energy < a.energy;
	}
};

int dist[500][24][7], from[500][24][7][3];

struct Edge {
	int u, s, e, cost;
};
vector<Edge> edges[500];

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		memset(dist, -1, sizeof(dist));
		memset(from, -1, sizeof(from));

		priority_queue<pair<int, Node>, vector<pair<int, Node>>, greater<pair<int, Node>>> q;
		for(int i = 0; i <= 0; i++) {
			Node start{0, i, 6};
			q.push(make_pair(0, start));
			dist[0][i][6] = 0;
		}

		int n, m;
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++) edges[i].clear();
		for(int i = 0; i < m; i++) {
			int u, v, s, e, cost;
			scanf("%d %d %d %d %d", &u, &v, &s, &e, &cost);
			edges[u - 1].push_back(Edge{v - 1, s, e, cost});
		}

		while(!q.empty()) {
			Node cur = q.top().second;
			int curDist = q.top().first;
			q.pop();
			if(curDist != dist[cur.city][cur.hour][cur.energy]) continue;

			{
				Node next = cur;
				next.energy = min(next.energy + 1, 6);
				next.hour = (next.hour + 1) % 24;

				int &ncost = dist[next.city][next.hour][next.energy];
				if(ncost == -1 or ncost > curDist + 1) {
					ncost = curDist + 1;
					q.push(make_pair(ncost, next));

					from[next.city][next.hour][next.energy][0] = cur.city;
					from[next.city][next.hour][next.energy][1] = cur.hour;
					from[next.city][next.hour][next.energy][2] = cur.energy;
				}
			}

			for(auto &e: edges[cur.city]) {
				if(cur.hour < e.s or cur.hour > e.e) continue;
				if(cur.energy < e.cost) continue;
				Node next{e.u, (cur.hour + e.cost) % 24, cur.energy - e.cost};
				int &ncost = dist[next.city][next.hour][next.energy];
				if(ncost == -1 or ncost > curDist + e.cost) {
					ncost = curDist + e.cost;
					q.push(make_pair(ncost, next));

					from[next.city][next.hour][next.energy][0] = cur.city;
					from[next.city][next.hour][next.energy][1] = cur.hour;
					from[next.city][next.hour][next.energy][2] = cur.energy;
				}
			}
		}

		int ans = 1 << 30;
		int city, hour, energy;
		for(int i = 0; i < 24; i++)
			for(int j = 0; j <= 6; j++) {
				int cand = dist[n - 1][i][j];
				if(cand != -1 and ans > cand) {
					ans = cand;
					city = n - 1;
					hour = i;
					energy = j;
				}
			}

		printf("Case %d: %d\n", kase, ans);
		/*
		do {
			printf("%d, %d, %d: %d\n", city, hour, energy, dist[city][hour][energy]);
			int ncity = from[city][hour][energy][0];
			int nhour = from[city][hour][energy][1];
			int nenergy = from[city][hour][energy][2];

			city = ncity;
			hour = nhour;
			energy = nenergy;
		} while(city != -1);
		*/
	}

	return 0;
}
