// Topological Sort
//
// Returns a topological ordering of g
// If G is not a DAG returns an empty vector
//
// O(n + m)

vector<int> g[MAX];

vector<int> topo_sort(int n) {
	vector<int> ret(n), vis(n);
	
	int pos = n-1;
	bool dag = true;
	function<void(int)> dfs = [&vis,&ret,&dag,&pos,&dfs] (int v) {
		vis[v] = 1;
		for(auto u : g[v]) {
			if(vis[u] == 1) dag = false;
			else if(!vis[u]) dfs(u);
		}
		ret[pos--] = v, vis[v] = 2;
	};

	for(int i=0; i<n; i++) if(!vis[i]) dfs(i);

	if(!dag) ret.clear();	
	return ret;
}
