#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cassert>

using namespace std;

#include "classes/TSPSolver.h"

double getMiliSecond(int time) {
	return 1000.0*time/CLOCKS_PER_SEC;
}

int main () {
	std::ios_base::sync_with_stdio(false);
	freopen("in.txt", "r", stdin);
	freopen("/Applications/XAMPP/xamppfiles/htdocs/tsp-chart/n-time.php", "w", stdout);
	cout.precision(2);
	cout.setf(ios::fixed);
	int n;
	cout << "<?php\necho json_encode(array(\n\t'data' => ";
	cout << "[" << endl;
	cout << "[\"Input Size\", \"Exponential Method\", \"Branch and Bound\", \"2-Approximation\"]," << endl;
	vector <int> input[3];
	while (cin >> n) {
		vector <vector <int> > mat(n, vector<int>(n, 0));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> mat[i][j];
			}
		}
		TSPSolver tsp(mat);
		cout << "[";
		cout << n;
		if (n < 12) {
			pair <int, int> ex = tsp.solveExp();
			cout << "," << getMiliSecond(ex.y);
		} else {
			cout << ", null";
		}
		if (n < 14) {
			pair <int, int> bnb = tsp.solveBnB();
			cout << "," << getMiliSecond(bnb.y);
			input[0].push_back(n);
			input[1].push_back(bnb.x);
		} else {
			cout << ", null";
		}
		pair <int, int> apx = tsp.solve2Apx();
		cout << "," << getMiliSecond(apx.y);
		if (n < 14) {
			input[2].push_back(apx.x);
		}
		cout << "]," << endl;
	}
	cout << "]));" << endl;

	fclose(stdout);
	freopen("/Applications/XAMPP/xamppfiles/htdocs/tsp-chart/solution.php", "w", stdout);
	cout << "<?php\necho json_encode(array(\n\t'data' => ";
	cout << "[" << endl;
	cout << "[\"Input Size\", \"Exact Solution\", \"2-Approximation\"]," << endl;
	for (int i = 0; i < int(input[0].size()); ++i) {
		cout << "[";
		cout << input[0][i];
		cout << ", ";
		cout << input[1][i];
		cout << ", ";
		cout << input[2][i];
		cout << "]," << endl;
	}
	cout << "]));" << endl;

	fclose(stdout);
	freopen("/Applications/XAMPP/xamppfiles/htdocs/tsp-chart/apx-ratio.php", "w", stdout);
	cout << "<?php\necho json_encode(array(\n\t'data' => ";
	cout << "[" << endl;
	cout << "[\"Input Size\", \"Approximation Ratio\"]," << endl;
	for (int i = 0; i < int(input[0].size()); ++i) {
		cout << "[";
		cout << input[0][i];
		cout << ", ";
		cout << 1.0 * input[2][i] / input[1][i];
		cout << "]," << endl;
	}
	cout << "]));" << endl;
	return 0;
}
