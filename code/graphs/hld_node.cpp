// Heavy-Light Decomposition - node
//
// SegTree of sum
// query / update of sum of nodes
//
// Complexities:
//
// Time:
// build - O(n)
// query_path - O(log^2 (n))
// update_path - O(log^2 (n))
// query_subtree - O(log(n))
// update_subtree - O(log(n))
//
// Space:
// O(n)
//
// Verification: https://codeforces.com/gym/102215/problem/D

vector<vector<int>> g(MAX);

namespace seg { ... }

namespace hld {
	int pos[MAX], sz[MAX], w[MAX], par[MAX], h[MAX], arr[MAX], t;

	void dfs1(int v, int p=-1) {
		sz[v] = 1;
		for(auto &u : g[v]) if(u != p) {
			par[u] = v;
			dfs1(u,v);
			sz[u] += sz[v];
			if(sz[u] > sz[g[v][0]] or g[v][0] == p) 
				swap(u, g[v][0]);
		}
	}

	void dfs2(int v, int p=-1) {
		arr[pos[v] = t++] = w[v];
		for(auto u : g[v]) if(u != p) {
			h[v] = (u == g[v][0] ? h[v] : u);
			dfs2(u,v);
		}
	}

	void build(int root=0) {
		par[root] = h[root] = root;
		t = 0;
		dfs1(root);
		dfs2(root);
		seg::build(); // arr is the arr that seg should build
	}

	ll query_path(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return seg::query(pos[b], pos[a]);
		return seg::query(pos[h[a]], pos[a]) + 
			   		query_path(pai[h[a]], b);
	}

	void update_path(int a, int b, int x) {
		if(pos[a] < pos[b]) swap(a, b);

		if(h[a] == h[b]) return (void) seg::update(pos[b], pos[a], x);
		
		seg::update(pos[h[a]], pos[a], x); 
		update_path(pai[h[a]], b, x);
	}

	ll query_subtree(int a) {
		return seg::query(pos[a], pos[a]+sz[a]-1);
	}

	void update_subtree(int a, int x) {
		seg::update(pos[a], pos[a]+sz[a]-1, x);
	}

	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}
