// BIT - Binary Indexed Tree (Fenwick Tree)
//
// all operations are 0-based
// can build an empty one or based on a vector
//
// Complexity:
// constructor: O(n)
// update, pref, query: O(log(n))

struct Bit {
	int n;
	vector<ll> tree;

	Bit(int n_) : n(n_), tree(n_ + 1) {}

	void update(int x, int p) {
		for (p++; p <= n; p += p & -p) tree[p] += x;
	}
	ll pref(int p) {
		ll ret = 0;
		for (p++; p > 0; p -= p & -p) ret += tree[p];
		return ret;
	}
	ll query(int l, int r) { return pref(r) - pref(l-1); }
};

/* linear build on a vector
Bit(vector<int> v) : n(v.size()), tree(v.size() + 1) {
	for (int i = 1; i <= n; i++) {
		tree[i] += v[i-1];
		if (i + (i & -i) <= n) tree[i + (i & -i)] += tree[i];
	}
}
*/
