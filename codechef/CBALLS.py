T = int(raw_input())

notPrime = [False] * 11000
primes = []
for i in range(2, 11000):
	if not notPrime[i]:
		primes += [i]
		for j in range(i * 2, 11000, i):
			notPrime[j] = True

while T > 0:
	T -= 1
	n = int(raw_input())
	balls = map(int, raw_input().split())
	ans = 9999999999999
	for prime in primes:
		curans = 0
		last = 0
		for ball in balls:
			tar = (ball + prime - 1) / prime * prime
			if tar < last:
				tar = last
			curans += tar - ball
			last = tar
		ans = min(ans, curans)
	
	print ans
