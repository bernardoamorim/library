// DFS
// Finds connected components and the parents in a tree

// Time complexity: O(v+e)

vector<vector<int> > g;
vector<int> par;
vector<int> v;

void dfs(int s) {
	v[s] = true;
	for (auto u: adj[s]) if(!v[u]) {
		dfs(u);
		par[u] = x; //if needs parent
	}
}
