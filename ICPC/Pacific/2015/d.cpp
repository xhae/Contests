#include <cstdio>
#include <algorithm>

using namespace std;

int main(void) {
	int arr[2][3];
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			scanf("%d", arr[i] + j);
	sort(arr[0], arr[0] + 3);
	sort(arr[1], arr[1] + 3);

	bool isAble = true;
	for(int i = 0; i < 3; i++)
		if(arr[0][i] != arr[1][i])
			isAble = false;
	if(arr[0][0] * arr[0][0] + arr[0][1] * arr[0][1] != arr[0][2] * arr[0][2]) isAble = false;

	printf("%s\n", isAble ? "YES" : "NO");
	return 0;
}
