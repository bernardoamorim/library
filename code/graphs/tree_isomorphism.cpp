// Tree isomorphism
// 
// thash() returns the hash of the tree. 
// Two trees are isomorph if their hash is the same.
// 
// Complexity: O(|V|.log(|V|))

map<vector<int>, int> mphash;

struct tree {
	int n;
	vector<vector<int>> g;
	vector<int> sz;

	tree(int n_) : n(n_), g(n_), sz(n_) {}

	vector<int> centroids(int root, int ssz) {
		vector<int> c;
		function<void(int,int)> dfs = [&] (int v, int p) {
			sz[v] = 1;
			bool cent = true;
			for(int u : g[v]) if(u != p) {
				dfs(u, v), sz[v] += sz[u];
				if(sz[u] > ssz/2) cent = false;
			}
			if(cent and ssz - sz[v] <= ssz/2) c.push_back(v);
		};
		dfs(root, -1);
		return c;
	}
	int fhash(int v, int p) {
		vector<int> h;
		for(int u : g[v]) if(u != p) 
			h.push_back(fhash(u, v));
		sort(all(h));
		if(not mphash.count(h)) mphash[h] = mphash.size();
		return mphash[h];
	}
	ll thash() {
		vector<int> cs = centroids(0, n);
		if(cs.size() == 1) return fhash(cs[0], -1);
		ll h1 = fhash(cs[0], cs[1]), h2 = fhash(cs[1], cs[0]);
		return (min(h1, h2) << 30) + max(h1, h2);
	}
};
