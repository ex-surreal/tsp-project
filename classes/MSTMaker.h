#ifndef MST_MAKER_H
#define MST_MAKER_H
#ifndef x
	#define x first
	#define y second
#endif
#include <queue>
#include <vector>

class MSTMaker
{
	vector <vector <int> > mat;
	int n, start;
public:
	MSTMaker(vector<vector <int> > &_mat) {
		this->mat = _mat;
		this->n = this->mat.size();
		this->start = this->n-1;
	}
	vector <vector <int> > getMST() {
		vector <int> D(n, 1<<29), parent(n, -1);
		vector <bool> flag(n, false);
		priority_queue <pair <int, int> > Q;
		D[this->start] = 0;
		parent[this->start] = this->start;
		Q.push(make_pair(-D[this->start], this->start));
		while (!Q.empty()) {
			int u = Q.top().y;
			Q.pop();
			if (flag[u]) {
				continue;
			}
			flag[u] = true;
			for (int v = 0; v < this->n; v++) {
				if (u == v) {
					continue;
				}
				if (D[v] > this->mat[u][v] && !flag[v]) {
					D[v] = this->mat[u][v];
					parent[v] = u;
					Q.push(make_pair(-D[v], v));
				}
			}
		}
		vector <vector <int> > adj(this->n);
		for (int i = 0; i < this->n; ++i) {
			if (parent[i] == i) {
				continue;
			}
			adj[i].push_back(parent[i]);
			adj[parent[i]].push_back(i);
		}
		return adj;
	}
	~MSTMaker() {
		this->mat.clear();
	}
	
};
#endif
