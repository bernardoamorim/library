// Verified: No
// SegTree
//
// Recursive with Lazy Propagation
// Query: sum of range [a, b]
// Update: adds x in all elements in range [a, b]
//
// Complexities:
// Time:
// build - O(n)
// query - O(log(n))
// update - O(log(n))
//
// Space: 
// O(n) 
namespace seg {
	ll seg[4*MAX], lazy[4*MAX];

	ll build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
	}

	void prop(int p, int l, int r) {
		if (!lazy[p]) return;
		int m = (l+r)/2;
		seg[2*p] += lazy[p]*(m-l+1);
		seg[2*p+1] += lazy[p]*(r-(m+1)+1);
		lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}

	ll query(int a, int b, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];
		prop(p, l, r);
		int m = (l+r)/2;
		return query(a, b, 2*p, l, m) + query(a, b, 2*p+1, m+1, r);
	}

	ll update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a) return seg[p];
		if (a <= l and r <= b) {
			seg[p] += (ll)x*(r-l+1);
			lazy[p] += x;
			return seg[p];
		}
		prop(p, l, r);
		int m = (l+r)/2;
		return seg[p] = update(a, b, x, 2*p, l, m) +
					    update(a, b, x, 2*p+1, m+1, r);
	}
};

// If you have a max seg, you can find out in O(log(n))
// the first and the smallest element >= val in a range:
//
// first position >=val in [a,b] (or -1 if it doesn't have one)


int get_left(int a, int b, int val, int p=1, int l=0, int r=n-1) {
	if (b < l or r < a or seg[p] < val) return -1;
	if (r == l) return l;
	int m = (l+r)/2;
	int x = get_left(a, b, val, 2*p, l, m);
	if (x != -1) return x;
	return get_left(a, b, val, 2*p+1, m+1, r);
}

// last position >= val in [a, b] (or -1 if it doesn't have one)

int get_right(int a, int b, int val, int p=1, int l=0, int r=n-1) {
	if (b < l or r < a or seg[p] < val) return -1;
	if (r == l) return l;
	int m = (l+r)/2;
	int x = get_right(a, b, val, 2*p+1, m+1, r);
	if (x != -1) return x;
	return get_right(a, b, val, 2*p, l, m);
}
