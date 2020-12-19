// Tarjan algotith for finding articulation points and bridges
//
// Assumes that the graph g is simple.
// If disconnected, it will find articulation and bridges considering only the component.
// Returns the articulation points.
//
// Complexity: O(|V| + |E|)

vector<vector<int>> g;

vector<vector<int>> g;

vector<bool> tarjan_ab(int n) {
	vector<int> in(n,-1), low(n), par(n,-1);
	vector<bool> art(n,false);
	int p = 0;
	
	function<int(int)> dfs = [&] (int v) {
		in[v] = low[v] = p++;
		int children = 0;
		for(auto u : g[v]) if(u != par[v]) {
			if(in[u] == -1) {
				children++;
				par[u] = v, dfs(u);
			
				if(low[u] >= in[v]) art[v] = true;
				// if(low[u] > in[v]) {v,u} is bridge
			
				low[v] = min(low[u], low[v]);
			}
			else low[v] = min(low[v], in[u]);
		}
		return children;
	};
	for(int i = 0; i < n; i++) if(in[i] == -1) art[i] = dfs(i) > 1;
	
	return art;
}
