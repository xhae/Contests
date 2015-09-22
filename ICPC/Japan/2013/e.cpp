#include<cstdio>
#include<vector>
#include<unordered_map>
#include<queue>
#include<functional>

using namespace std;

int hori,vert;
int ten[10];


int find_zero(int a)
{
	int idx=0;
	while(1)
	{
		if(a%10==0)	break;
		idx++;
		a/=10;
	}
	return idx;
}

int change(int a,int idx1,int idx2)
{
	int t1,t2;
	t1=(a/ten[idx1])%10;
	t2=(a/ten[idx2])%10;
	a-=t1*ten[idx1];
	a-=t2*ten[idx2];
	a+=t1*ten[idx2];
	a+=t2*ten[idx1];
	return a;
}

vector<int> hor(int a)
{
	vector<int> result;
	int temp=find_zero(a);
	result.push_back(change(a,temp,(temp+1)%9));
	result.push_back(change(a,temp,(temp+8)%9));
	return result;
}

vector<int> ver(int a)
{
	vector<int> result;
	int temp=find_zero(a);
	result.push_back(change(a,temp,(temp+3)%9));
	result.push_back(change(a,temp,(temp+6)%9));
	return result;	
}

unordered_map<int, int> indHash;

void backtr(int len, int stat) {
	if(len == 9) {
		int n = indHash.size();
		indHash[stat] = n;
		return;
	}

	bool isExist[9] = {false, };
	int temp = stat;
	for(int i = 0; i < len; i++) {
		isExist[temp % 10] = true;
		temp /= 10;
	}

	for(int i = 0; i < 9; i++)
		if(!isExist[i])
			backtr(len + 1, stat * 10 + i);
}

vector<int> hedge[400000];
vector<int> vedge[400000];
int dist[400000];

int main() {
	int temp=1;
	for(int i=0;i<10;i++)
	{
		ten[i]=temp;
		temp*=10;
	}

	backtr(0, 0);
	for(auto &e: indHash) {
		int idx = e.first;
		vector<int> h=hor(idx);
		vector<int> v=ver(idx);
		for(auto nidx: h) hedge[e.second].push_back(indHash[nidx]);
		for(auto nidx: v) vedge[e.second].push_back(indHash[nidx]);
	}

	while(scanf("%d %d",&hori,&vert), hori != 0) {
		int start=0,obj=0;

		for(int i=0;i<9;i++)
		{
			start*=10;
			scanf("%d",&temp);
			start+=temp;
		}

		for(int i=0;i<9;i++)
		{
			obj*=10; 
			scanf("%d",&temp);
			obj+=temp;
		}

		start = indHash[start];
		obj = indHash[obj];

		priority_queue<pair<int,int>, vector<pair<int,int> > , greater<pair<int,int> > > pq;
		pq.push(make_pair(0, start));
		memset(dist, -1, sizeof(dist));
		dist[start] = 0;

		while(!pq.empty()) {
			int val=pq.top().first, idx=pq.top().second;
			pq.pop();
			if(dist[idx] < val)	continue;

			for(auto next: hedge[idx])
				if(dist[next] == -1 or dist[next] > val + hori) {
					dist[next] = val + hori;
					pq.push(make_pair(dist[next], next));
				}
			for(auto next: vedge[idx])
				if(dist[next] == -1 or dist[next] > val + vert) {
					dist[next] = val + vert;
					pq.push(make_pair(dist[next], next));
				}
		}
		printf("%d\n",dist[obj]);
	}
}
