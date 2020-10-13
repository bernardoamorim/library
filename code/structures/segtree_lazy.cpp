// SegTree with Lazy Propagation
//
// Made to be modified
// S is seg type and T is lazy tipe
// apply(s,t,l,r) apply update s to a node with value t from l to r
// upd_lazy(s1,s2) update s2 based on s1
//
// query: sum [a, b]
// update: summates x im each element in [a, b]
//
// build - O(n)
// query - O(log(n))
// update - O(log(n))

template<typename T, typename S> class segtree {
private:
	int sz;
	vector<T> seg;
	vector<S> lazy;
	T id = 0; 
	S lazy_id = 0; 

	T merge(T t1, T t2) { return t1 + t2; }
	T apply(S s, T t, int l, int r) { return s*(r-l+1) + t; }
	S upd_lazy(S s1, S s2) { return s1 + s2; } 
public:
	T build(vector<T>& v, int p, int l, int r) {
		if (l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = merge(build(v,2*p, l, m), build(v,2*p+1, m+1, r));
	}
	void prop(int p, int l, int r) {
		if(lazy[p] == lazy_id) return;
		S s = lazy[p];
		int m = (l+r)/2;
		seg[2*p] = apply(s, seg[2*p], l, m);
		seg[2*p+1] = apply(s, seg[2*p+1], m+1, r);
		lazy[2*p] = upd_lazy(s, lazy[2*p]);
		lazy[2*p+1] = upd_lazy(s, lazy[2*p+1]);
		lazy[p] = lazy_id;
	}
	T query(int s, int e) { return query(s, e, 1, 0, sz-1); }
	T query(int s, int e, int p, int l, int r) {
		if(e < l or r < s) return id;
		if(s <= l and r <= e) return seg[p];
		prop(p, l, r);
		int m = (l+r)/2;
		return merge(query(s, e, 2*p, l, m), query(s, e, 2*p+1, m+1, r));
	}
	T upd(int s, int e, S x) { return upd(s, e, x, 1, 0, sz-1); }
	T upd(int s, int e, S x, int p, int l, int r) {
		if(e < l or r < s) return seg[p];
		if(s <= l and r <= e) {
			seg[p] = apply(x, seg[p], l, r);
			lazy[p] = upd_lazy(x, lazy[p]);
			return seg[p];
		}
		prop(p, l, r);
		int m = (l+r)/2;
		return seg[p] = merge(upd(s, e, x, 2*p, l, m), upd(s, e, x, 2*p+1, m+1, r));
	}
	segtree(int sz_) : sz(sz_) {
		seg.resize(4*sz, id);
		lazy.resize(4*sz, lazy_id);
	}
	segtree(int sz_, vector<T> v) : sz(sz_) {
		seg.resize(4*sz, id);
		lazy.resize(4*sz, lazy_id);
		build(v,1,0,sz-1);
	}
};

// TO ADD LEFT AND RIGHT
