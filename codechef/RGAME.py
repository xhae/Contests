T = int(raw_input())
MOD = 1000000007
while T > 0:
	T -= 1
	n = int(raw_input())
	n += 1
	data = map(int, raw_input().split())

	mul = []
	mulsum = []
	for i in range(n - 1):
		mul += [data[i] * data[i + 1] % MOD]
		if i == 0:
			mulsum += [mul[0]]
		else:
			mulsum += [mulsum[-1] + mul[i]]

	twopow = [1]
	for i in range(0, n):
		twopow += [twopow[-1] * 2 % MOD]
	
	dp = [0] * n
	dpsum = 0
	curmul = 0
	dsum = 0
	for i in range(n - 2, 0, -1):
		dpsum = (dpsum + dp[i + 1]) % MOD
		dp[i] = dpsum
		curmul = (curmul + mul[i] * (twopow[n - i - 2])) % MOD
		dsum = (dsum + data[i + 1] * twopow[n - i - 2]) % MOD
		cross = data[i - 1] * dsum
		dp[i] += curmul
		dp[i] += cross
		dp[i] %= MOD

	ans = 0
	for i in range(0, n - 1):
		nind = n - i - 2
		if i > 0:
			ans += mulsum[i - 1] * twopow[nind]
		ans += data[0] * data[i + 1] * twopow[nind] + dp[i + 1]
		ans %= MOD
	ans += mulsum[n - 2]
	ans %= MOD

	print ans
