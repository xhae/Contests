T = int(raw_input())
while T > 0:
	T -= 1
	n, k, m = map(int, raw_input().split())
	todos = map(int, raw_input().split())
	dones = map(int, raw_input().split())
	whites = map(int, raw_input().split())
	blacks = map(int, raw_input().split())

	buttons = sorted(whites + blacks)
	lefts = sorted([todos[i] - dones[i] for i in range(len(todos))])

	ib = len(buttons) - 1
	il = len(lefts) - 1

	ans = 0
	while il >= 0 and ib >= 0:
		while ib >= 0 and buttons[ib] > lefts[il]:
			ib -= 1
		lefts[il] -= buttons[ib]
		ans += lefts[il]
		il -= 1
		ib -= 1
	
	while il >= 0:
		ans += lefts[il]
		il -= 1

	print ans
