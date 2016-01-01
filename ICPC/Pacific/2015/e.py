n = int(raw_input())
arr = []
for i in range(n):
	v = int(raw_input())
	arr += [v]
arr = sorted(arr)
ans = 99999999
for i in range(n):
	opp = n - i - 1
	if i > opp:
		break
	ans = min(ans, arr[i] + arr[opp])
print ans
