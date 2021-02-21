// Tree isomorphism
// 
// tree_hash(v, sz) returns the hash of the tree that contains
// vertex v and has size sz and does not contain the vertices 
// marked as dead (be careful)
// Two trees are isomorph if their hash is the same
// 
// Complexity: O(|V|.log(|V|)

vector<int> g[MAX];
int sz[MAX];
bool dead[MAX];

vector<int> centroids(int root, int ssz) {
	vector<int> c;
	
	function<void(int,int)> dfs = [&] (int v, int p) {
		sz[v] = 1;
		bool cent = true;
		for(int u : g[v]) if(u != p and not dead[u]) {
			dfs(u, v), sz[v] += sz[u];
			if(sz[u] > ssz/2) cent = false;
		}
		if(cent and ssz - sz[v] <= ssz/2) c.push_back(v);
	};
	dfs(root, -1);

	return c;
}

map<vector<int>,int> mphash;

int fhash(int v, int p) {
	vector<int> h;
	for(int u : g[v]) if(u != p and not dead[u]) 
		h.push_back(fhash(u, v));
	sort(all(h));
	if(not mphash.count(h)) 
		mphash[h] = mphash.size();
	return mphash[h];
}

ll tree_hash(int root, int ssz) {
	vector<int> cs = centroids(root, ssz);
	for(int c : cs) dead[c] = true;
	
	vector<ll> vh;
	for(int c : cs) vh.push_back(fhash(c, -1));
	
	if(vh.size() > 1) {
		if(vh[0] > vh[1]) swap(vh[0], vh[1]);
		return (vh[0] << 30) + vh[1];
	}
	return vh[0];
}
