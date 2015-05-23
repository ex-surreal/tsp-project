#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H
#ifndef x
	#define x first
	#define y second
#endif

#include "MSTMaker.h"

class TSPSolver {
	private:
	int n;
	int first;
	int minCostBnB;
	int minCost;
	vector <int> preOrder;
	vector <vector <int> > mat, tree;

	void rec(int u, int mask, int cost = 0) {
		if (((1<<this->n)-1) == mask) {
			this->minCost = min(this->minCost, cost + this->mat[u][this->first]);
			return;
		}
		for (int v = 0; v < this->n; v++) {
			if (u == v) {
				continue;
			}
			if (!((mask>>v)&1)) {
				rec(v, mask|(1<<v), cost + this->mat[u][v]);
			}
		}
	}

	void recBnB(int u, int mask, int cost = 0) {
		if (mask == ((1<<this->n) - 1)) {
			this->minCostBnB = min(this->minCostBnB, cost + this->mat[u][this->first]);
			return;
		}
		for (int v = 0; v < this->n; v++) {
			if (u == v) {
				continue;
			}
			if (!((mask>>v)&1) && cost + this->mat[u][v] < this->minCostBnB) {
				recBnB(v, mask|(1<<v), cost + this->mat[u][v]);;
			}
		}
	}

	void dfs(int u, int w) {
		preOrder.push_back(u);
		for (int i = 0; i < int(this->tree[u].size()); ++i) {
			int v = this->tree[u][i];
			if (v != w) {
				dfs(v, u);
			}
		}
	}
	public:
	TSPSolver(vector <vector <int> > &_mat) {
		this->n     = _mat.size();
		this->first = 2;
		this->mat   = _mat;
	}

	~TSPSolver() {
		mat.clear();
		preOrder.clear();
		tree.clear();
	}

	pair<int, int> solveExp() {
		int start = clock();
		this->minCost = 1<<29;
		rec(this->first, 1<<this->first);
		int end = clock();
		return make_pair(this->minCost, end - start);
	}

	pair <int, int> solve2Apx() {
		int start = clock();
		int ans = 0;
		MSTMaker mst(this->mat);
		this->tree = mst.getMST();
		this->preOrder.clear();
		this->dfs(0, 0);
		for (int i = 0; i < this->n; i++) {
			ans += this->mat[preOrder[i]][preOrder[(i+1)%this->n]];
		}
		int end = clock();
		return make_pair(ans, end-start);
	}

	pair <int, int> solveBnB() {
		int start = clock();
		this->minCostBnB = 1<<29;
		recBnB(this->first, 1<<this->first);
		int end = clock();
		return make_pair(this->minCostBnB, end-start);
	}
};
#endif
