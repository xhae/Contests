import Queue

MOD = 1000000007
def modinv(tar):
	ret = 1
	for i in range(30, -1, -1):
		ret = ret * ret % MOD
		if ((MOD - 2) & (1 << i)) > 0:
			ret = ret * tar % MOD
	return ret

facts = [1]
ifacts = [1]
for i in range(1, 100001):
	facts += [facts[i - 1] * i % MOD]
	ifacts += [modinv(facts[i])]

T = int(raw_input())

def combi(n, r):
	return facts[n] * ifacts[r] % MOD * ifacts[n - r] % MOD

def count(n, forbids):
	cnt = {}
	for forbid in forbids:
		for u in forbid:
			if u not in cnt:
				cnt[u] = 0
			cnt[u] += 1
	for u in cnt:
		if cnt[u] > 2:
			return 0
	edges = {}
	for forbid in forbids:
		u, v = forbid
		if u not in edges:
			edges[u] = []
		if v not in edges:
			edges[v] = []
		edges[u] += [v]
		edges[v] += [u]
	
	isVisited = set()
	lengths = []
	for u in cnt:
		if cnt[u] == 1 and u not in isVisited:
			q = Queue.Queue()
			q.put(u)
			isVisited.add(u)
			length = 0
			while not q.empty():
				cur = q.get()
				length += 1
				for ncur in edges[cur]:
					if ncur in isVisited:
						continue
					q.put(ncur)
					isVisited.add(ncur)
			lengths += [length]
	
	if sum(lengths) != len(edges):
		return 0

	totElements = n - len(edges) + len(lengths)
	ret = combi(totElements, len(lengths))
	for i in range(len(lengths)):
		ret = ret * 2 % MOD
	ret = ret * facts[len(lengths)] % MOD
	ret = ret * facts[n - len(edges)] % MOD
	return ret
	
while T > 0:
	T -= 1
	n, m = map(int, raw_input().split())
	forbidden = []
	for i in range(m):
		u, v = map(int, raw_input().split())
		forbidden += [[u, v]]
	
	ans = 0
	for i in range(1 << m):
		curForbids = []
		cnt = 0
		for j in range(0, m):
			if (i & (1 << j)) > 0:
				curForbids += [forbidden[j]]
				cnt += 1
		ans += count(n, curForbids) * (1 if cnt % 2 == 0 else -1)
		ans = (ans + MOD) % MOD
	
	print ans
