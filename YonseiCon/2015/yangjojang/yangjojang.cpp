#include <string>
#include <iostream>

using namespace std;

int main(void) {
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		int maxV = -1;
		string name;
		while(n--) {
			string cname;
			int cv;
			cin >> cname >> cv;
			if(cv > maxV) {
				maxV = cv;
				name = cname;
			}
		}

		cout << name << "\n";
	}

	return 0;
}
