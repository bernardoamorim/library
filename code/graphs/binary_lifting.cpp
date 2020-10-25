// Binary Lifting (LCA implemented)
//
// bl(order of graph, root = 0)
//
// construct O(n.log(n));
// lca O(log(n))

vector<int> g[MAX];

struct binary_lifting {
	vector<vector<int>> lift;
	int n, lgn, ctr = 0;
	vector<int> in, out;
	
	void dfs(int v) {
		in[v] = ctr++;
		int aux = 0;
		for(auto u : g[v]) {
			if(in[u] == -1) {
				lift[0][u] = v;
				dfs(u);
			}
			aux++;
		}
		out[v] = ctr++;
	}

	binary_lifting(int n_, int root = 0) : n(n_), in(n_,-1), out(n_) {
		lgn = ceil(log2(n));
		lift = vector<vector<int>>(lgn, vector<int>(n));
		dfs(root);

		for(int i=1; i < lgn; i++) for(int j=0; j<n; j++)
			lift[i][j] = lift[i-1][lift[i-1][j]];
	}
	
	bool anc(int u, int v) { return in[u] <= in[v] and out[u] >= out[v]; }

	int lca(int u, int v) {
		if(anc(u,v)) return u;
		if(anc(v,u)) return v;
		for(int i = lgn-1; i >= 0; i--)
			if(!anc(lift[i][u], v)) u = lift[i][u];
		return lift[0][u];
	}
};
