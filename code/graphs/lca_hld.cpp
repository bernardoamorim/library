// LCA with HLD
//
// Assumes a vertice is it's own ancestor,
// To build just call build(root)
//
// Complexities:
// Time:
// build - O(n)
// lca - O(log(n))
//
// Space:
// O(n)
//
// Verification: https://www.spoj.com/problems/LCA/

namespace hld {
	vector<int> w(MAX), idx(MAX), par(MAX), h(MAX);
	int t;

	void dfs1(int v) {
		w[v] = 1;
		for(auto& u : g[v]) if(!w[u]) {
			par[u] = v;
			dfs1(u);
			w[v] += w[u];
			if(w[u] > w[g[v][0]]) swap(u, g[v][0]);
		}
	}
	void dfs2(int v) {	
		idx[v] = t;
		for(auto u : g[v]) if(!idx[u]) { 
			h[u] = (u == g[v][0] ? h[v] : u);
			++t; dfs2(u);
		}
	}

	void build(int root) {
		for(int i=0; i<n; i++) 
			par[i] = h[i] = idx[i] = w[i] = 0;
		par[root] = h[root] = root;
		dfs1(root);
		t=1;
		dfs2(root);
	}

	int lca(int a, int b) {
		if(idx[a] < idx[b]) swap(a,b);
		return h[a] == h[b] ? b : lca(par[h[a]],b);
	}
}
