// Lowest Common Ancertor with Heavy-Light Decomposition
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
	int t, sz[MAX], pos[MAX], par[MAX], h[MAX];

	void dfs1(int v, int p=-1) {
		sz[v] = 1;
		for(auto& u : g[v]) if(u != p) {
			par[u] = v;
			dfs1(u);
			sz[v] += sz[u];
			if(sz[u] > sz[g[v][0]] or g[v][0] == p) swap(u, g[v][0]);
		}
	}
	void dfs2(int v, int p=-1) {	
		pos[v] = t++;
		for(auto u : g[v]) if(u != p) { 
			h[u] = (u == g[v][0] ? h[v] : u);
			dfs2(u);
		}
	}

	void build(int root=0) {
		par[root] = h[root] = root;
		t = 0;
		dfs1(root);
		dfs2(root);
	}

	int lca(int a, int b) {
		if(pos[a] < pos[b]) swap(a,b);
		return h[a] == h[b] ? b : lca(par[h[a]],b);
	}
}
