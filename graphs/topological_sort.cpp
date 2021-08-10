// Topological Sort
//
// Returns a topological ordering of g
// If G is not a DAG returns an empty vector
//
// O(n + m)

vector<int> g[MAX];

vector<int> topo_sort(int n) {
	vector<int> ret(n), vis(n);
	
	int it = n-1;
	bool dag = true;
	function<void(int)> dfs = [&] (int v) {
		vis[v] = 1;
		for(int u : g[v]) {
			if(vis[u] == 1) dag = false;
			else if(not vis[u]) dfs(u);
		}
		ret[it--] = v, vis[v] = 2;
	};

	for(int i = 0; i < n; i++) if(not vis[i]) dfs(i);

	if(not dag) ret.clear();	
	return ret;
}
