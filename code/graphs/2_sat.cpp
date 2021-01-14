// 2-SAT
// 
// Returns if the logic statement is satisfiable and the boolean values to do so
// Statement has the form (x v y) ^ (x v z) ^ (y => w)...
// 
// O(|V| + |E|), where |V| = number of variables and |E| is the 
// number of logical statements.

vector<int> g[2 * MAX], gt[2 * MAX];

// pair<int,vector<int>> kosaraju(int n) returns {ncomps, comp};
// In comp, if there is a path from comp[i] to comp[j], comp[i] > comp[j]

struct _2sat {
	int n;

	_2sat(int _n) : n(_n) {}

	int no(int id) { return (id + n) % (2 * n); }

	void add(int x, int y) {
		g[x].push_back(y), g[no(y)].push_back(no(x));
		gt[y].push_back(x), gt[no(x)].push_back(no(y));
	}

	void add_or(int x, int y) { add(no(x), y); }

	void add_imply(int x, int y) { add(x, y); }

	pair<bool,vector<bool>> solve() {
		vector<bool> assignment(n); // to be tested

		auto [n_comps, comp] = kosaraju(2 * n);
		bool sat = true;
		for(int i = 0; i < n; i++) {
			if(comp[i] == comp[no(i)]) sat = false;
			else assignment[i] = comp[i] < comp[no(i)];
		}
		if(!sat) assignment.clear();
		return {sat, assignment};
	}
};
