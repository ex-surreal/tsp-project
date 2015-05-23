#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

int main () {
	freopen("int.txt", "w", stdout);
	srand(time(NULL));
	int tst = 22;
	vector <int> n(tst);
	for (int cas = 0; cas < tst; ++cas) {
		n[cas] = cas+3;
	}
	sort(n.begin(), n.end());
	for (int cas = 0; cas < tst; ++cas) {
		cout << n[cas] << endl;
		vector <vector <int> > mat(n[cas], vector <int>(n[cas], 0));
		for (int i = 0; i < n[cas]; ++i) {
			for (int j = i+1; j < n[cas]; ++j) {
				mat[j][i] = mat[i][j] = rand()%100 + 1;
			}
		}
		for (int i = 0; i < n[cas]; ++i) {
			for (int j = 0; j < n[cas]; ++j) {
				cout << mat[i][j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}
