// DSU
//
// Unites sets and finds its class
//
// O(a(n)) ~= O(1)

struct DSU {
	vector<int> id, sz;
	
	dsu(int sz_) : id(sz_), sz(sz_, 1) { 
		iota(id.begin(), id.end(), 0); 
	}
	
	int find(int a) { 
		return id[a] = a == id[a] ? a : find(id[a]); 
	}
	
	void unite(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) 
			return;
		if (sz[a] < sz[b]) 
			swap(a, b);
		sz[a] += sz[b], id[b] = a;
	}
};
