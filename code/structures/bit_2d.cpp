// BIT - Binary Indexed Tree (Fenwick Tree) with range update
//
// all operations are 0-based
// can build an empty one or based on a vector
//
// Complexity:
// constructor: O(n)
// update, pref, sum: O(log(n))

struct Bit_2D {
	int n;
	vector<ll> tree[2];
	
	Bit_2D(int n_) : n(n_) { 
		tree[0].resize(n+1), tree[1].resize(n+1); 
	}
	
	void update_(ll x, int p, int w) {
		for (p++; p <= n; p += p & -p) tree[w][p] += x;
	}
	ll pref_(int p, int w) {
		ll ret = 0;
		for (p++; p > 0; p -= p & -p) ret += tree[w][p];
		return ret;
	}
	void update(ll x, int l, int r) {
		update_(x, l, 0), update_(-x, r+1, 0);
		update_(-x*l, l, 1), update_(x*(r+1), r+1, 1);
	}
	ll pref(int p) { return pref_(p,0) * (p+1) + pref_(p,1); }
	ll query(int l, int r) { return pref(r) - pref(l-1); }
};

/* linear build on a vector
Bit_2D(vector<int> v) : n(v.size()) {
	tree[0].resize(n+1), tree[1].resize(n+1);
	for (int i = 1; i <= n; i++) {
		tree[1][i] += v[i-1];
		if (i + (i & -i) <= n) 
			tree[1][i + (i & -i)] += tree[1][i];
	}
}
*/
