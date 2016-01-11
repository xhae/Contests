#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

vector<long long> times;
int n, q;

long long lastTime[50001], lastPos[50001], speed[50001];
struct Query {
	int type;
	long long time;
	int player;
	long long newSpeed;
	bool operator < (const Query &a) const {
		if(time != a.time) return time < a.time;
		else if(type != a.type) return type > a.type;
		else if(type == 1) return newSpeed < a.newSpeed;
		return false;
	}
} queries[100000];

const int base = (1 << 17);
int iTree[base << 1], delta[base << 1];

void pushdown(int cs, int ce, int ind) {
	if(delta[ind] == 0) return;
	if(cs + 1 == ce) iTree[ind] = delta[ind];
	else delta[ind * 2] = delta[ind * 2 + 1] = delta[ind];
	delta[ind] = 0;
}

void update(int cs, int ce, int ts, int te, int ind, int v) {
	if(cs >= ce or cs >= te or ts >= ce or ts >= te) return;
	pushdown(cs, ce, ind);
	if(cs == ts and ce == te) {
		delta[ind] = v;
		pushdown(cs, ce, ind);
	} else {
		int mid = (cs + ce) / 2;
		update(cs, mid, ts, min(te, mid), ind * 2, v);
		update(mid, ce, max(ts, mid), te, ind * 2 + 1, v);
	}
}

int getVal(int cs, int ce, int ts, int te, int ind) {
	if(cs >= ce or cs >= te or ts >= ce or ts >= te) return 0;
	pushdown(cs, ce, ind);
	if(cs == ts and ce == te) return iTree[ind];
	int mid = (cs + ce) / 2;
	return max(getVal(cs, mid, ts, min(te, mid), ind * 2), getVal(mid, ce, max(ts, mid), te, ind * 2 + 1));
}

long long getPos(int ind, long long time) {
	return lastPos[ind] + (time - lastTime[ind]) * speed[ind];
}

unordered_map<long long, int> tindHash;

int main(void) {
	scanf("%d %d", &n, &q);
	for(int i = 0; i < q; i++) {
		auto &query = queries[i];
		scanf("%d %lld", &query.type, &query.time);
		if(query.type == 1) scanf("%d %lld", &query.player, &query.newSpeed);
		times.push_back(query.time);
	}

	sort(times.begin(), times.end());
	times.erase(unique(times.begin(), times.end()), times.end());
	for(int i = 0; i < times.size(); i++) tindHash[times[i]] = i;

	update(0, base, 0, times.size(), 1, 1);

	sort(queries, queries + q);

	for(int i = 0; i < q; i++) {
		auto cq = queries[i];
		if(cq.type == 1) {
			int who = cq.player;
			int posind = -1;
			{
				int s = tindHash[cq.time], e = times.size();
				while(e - s > 3) {
					int m1 = (s * 2 + e) / 3;
					int who1 = getVal(0, base, m1, m1 + 1, 1);
					long long curLeadPos1 = getPos(who1, times[m1]);
					long long myPos1 = getPos(cq.player, cq.time);
					myPos1 += (times[m1] - cq.time) * cq.newSpeed;
					
					int m2 = (s + e * 2) / 3;
					int who2 = getVal(0, base, m1, m1 + 1, 1);
					long long curLeadPos2 = getPos(who2, times[m2]);
					long long myPos2 = getPos(cq.player, cq.time);
					myPos2 += (times[m2] - cq.time) * cq.newSpeed;

					long long gap1 = myPos1 - curLeadPos1;
					long long gap2 = myPos2 - curLeadPos2;

					if(gap1 > 0) { posind = m1; break; }
					if(gap2 > 0) { posind = m2; break; }

					if(gap1 < gap2) s = m1;
					else e = m2 + 1;
				}

				for(int i = s; i < e and posind == -1; i++) {
					int who = getVal(0, base, i, i + 1, 1);
					long long curLeadPos = getPos(who, times[i]);
					long long myPos = getPos(cq.player, cq.time);
					myPos += (times[i] - cq.time) * cq.newSpeed;
					
					long long gap = myPos - curLeadPos;
					if(gap > 0) {
						posind = i;
						break;
					}
				}
			}

			int upper = -1, lower = times.size(); 
			if(posind != -1) {
				{
					int s = posind, e = times.size();
					while(s < e) {
						int mid = (s + e) / 2;
						int who = getVal(0, base, mid, mid + 1, 1);
						long long curLeadPos = getPos(who, times[mid]);
						long long myPos = getPos(cq.player, cq.time);
						myPos += (times[mid] - cq.time) * cq.newSpeed;

						if(myPos > curLeadPos) upper = s = mid + 1;
						else e = mid;
					}
				}
				{
					int s = tindHash[cq.time], e = posind + 1;
					while(s < e) {
						int mid = (s + e) / 2;
						int who = getVal(0, base, mid, mid + 1, 1);
						long long curLeadPos = getPos(who, times[mid]);
						long long myPos = getPos(cq.player, cq.time);
						myPos += (times[mid] - cq.time) * cq.newSpeed;

						if(myPos > curLeadPos) lower = e = mid;
						else s = mid + 1;
					}
				}
			}
			
			long long myPos = getPos(cq.player, cq.time);
			lastPos[cq.player] = myPos;
			lastTime[cq.player] = cq.time;
			speed[cq.player] = cq.newSpeed;

			if(lower < upper) update(0, base, lower, upper, 1, cq.player); 
		} else {
			int tInd = lower_bound(times.begin(), times.end(), cq.time) - times.begin();
			int who = getVal(0, base, tInd, tInd + 1, 1);
			printf("%lld\n", getPos(who, times[tInd]));
		}
	}

	return 0;
}
