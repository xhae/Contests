def f(v):
	if v < 10:
		return v
	s = 0
	while v > 0:
		s += v % 10
		v /= 10
	return f(s)

def getSum(tar, arr):
	tot = sum(arr)
	ret = tot * (tar / len(arr))
	tar %= len(arr)
	for i in range(0, tar):
		ret += arr[i]
	return ret

T = int(raw_input())
while T > 0:
	T -= 1
	s, d, l, r = map(int, raw_input().split())

	cur = s
	arr = []
	while True:
		tar = f(cur)
		if len(arr) > 0 and arr[0] == tar:
			break
		arr += [tar]
		cur += d

	print getSum(r, arr) - getSum(l - 1, arr)
