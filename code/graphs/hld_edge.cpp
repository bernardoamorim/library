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

vector<vector<ii>> g(MAX); // [a] = {b,weight (a -> b)}

namespace seg { ... }

namespace hld {
	int pos[MAX], sz[MAX], up[MAX], par[MAX], h[MAX], arr[MAX], t;

	void dfs1(int v, int p=-1) {
		sz[v] = 1;
		for(auto &u : g[v]) if(u.f != p) {
			up[u.f] = u.s;
			par[u.f] = v;
			dfs1(u.f,v);
			sz[u.f] += sz[v];
			if(sz[u.f] > sz[g[v][0]] or g[v][0] == p) 
				swap(u, g[v][0]);
		}
	}

	void dfs2(int v, int p=-1) {
		arr[pos[v] = t++] = up[v];
		for(auto u : g[v]) if(u.f != p) {
			h[v] = (u.f == g[v][0] ? h[v] : u.f);
			dfs2(u.f,v);
		}
	}

	void build(int root=0) {
		par[root] = h[root] = root;
		t = 0;
		dfs1(root);
		dfs2(root);
		seg::build(); // arr is the array that seg should build
	}

	ll query_path(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return seg::query(pos[b]+1, pos[a]);
		return seg::query(pos[h[a]], pos[a]) + 
			   		query_path(pai[h[a]], b);
	}

	void update_path(int a, int b, int x) {
		if(pos[a] < pos[b]) swap(a, b);

		if(h[a] == h[b]) return (void) seg::update(pos[b]+1, pos[a], x);
		
		seg::update(pos[h[a]], pos[a], x); 
		update_path(pai[h[a]], b, x);
	}

	ll query_subtree(int a) {
		return seg::query(pos[a]+1, pos[a]+sz[a]-1);
	}

	void update_subtree(int a, int x) {
		seg::update(pos[a]+1, pos[a]+sz[a]-1, x);
	}

	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}
