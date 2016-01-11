T = int(raw_input())
while T > 0:
	T -= 1
	n, m = map(int, raw_input().split())
	field = []
	mx = m
	Mx = -1
	my = n
	My = -1
	for i in range(n):
		field += [raw_input()]
		for j in range(m):
			if field[i][j:j + 1] == '*':
				mx = min(mx, j)
				Mx = max(Mx, j)
				my = min(my, i)
				My = max(My, i)

	ans = 0
	if My >= 0:
		gap = max(Mx - mx, My - my) + 1
		ans = gap / 2 + 1
	
	print ans
