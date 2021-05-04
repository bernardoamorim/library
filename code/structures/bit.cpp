// BIT - Binary Indexed Tree (Fenwick Tree) with range update
//
// all operations are 0-based
// can build an empty one or based on a vector
//
// Complexity:
// constructor: O(n)
// add, pref, sum: O(log(n))

struct Bit {
	int n;
	vector<ll> tree[2];
	
	Bit(int n_) : n(n_) { 
		tree[0].resize(n+1), tree[1].resize(n+1); 
	}
	
	Bit(vector<int> v) : n(v.size()) {
		tree[0].resize(n+1), tree[1].resize(n+1);
		for (int i = 1; i <= n; i++) {
			tree[1][i] += v[i-1];
			if (i + (i & -i) <= n) 
				tree[1][i + (i & -i)] += tree[1][i];
		}
	}
	
	void add_(ll x, int p, int w) {
		p++;
		while (p <= n) 
			tree[w][p] += x, p += p & -p;
	}
	
	ll pref_(int p, int w) {
		ll ret = 0;
		p++;
		while (p > 0) 
			ret += tree[w][p], p -= p & -p;
		return ret;
	}
	
	void add(ll x, int l, int r = -1) {
		if (r == -1) 
			r = l;
		add_(x, l, 0), add_(-x, r+1, 0);
		add_(-x*l, l, 1), add_(x*(r+1), r+1, 1);
	}
	
	ll pref(int p) { 
		return pref_(p,0) * (p+1) + pref_(p,1); 
	}
	
	ll sum(int l, int r) { 
		return pref(r) - pref(l-1); 
	}
};
