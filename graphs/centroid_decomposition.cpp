// Centroid-decomposition
//
// cdecomp(root, size of tree) builds the centroid-decomposition tree
// (ctree) and returns its root.
// All vertices are dead after its execution.
//
// Complexity: O(|V|.log_2(|V|))

vector<int> g[MAX], ctree[MAX];
int sz[MAX];
bool dead[MAX];

int centroid(int root, int ssz) {
	int c;
	function<void(int,int)> dfs = [&] (int v, int p) {
		sz[v] = 1;
		bool cent = true;
		for (int u : g[v]) if (u != p and not dead[u]) {
			dfs(u, v), sz[v] += sz[u];
			if(sz[u] > ssz/2) cent = false;
		}
		if (cent and ssz - sz[v] <= ssz/2) c = v;
	};
	dfs(root, -1);
	return c;
}

int cdecomp(int v, int ssz) {
	int c = centroid(v, ssz);
	dead[c] = true;
	for (int u : g[c]) if (not dead[u]) {
		int nssz = (sz[u] > sz[c] ? ssz - sz[c] : sz[u]);
		ctree[c].push_back(cdecomp(u, nssz));
	}
	return c;
}
