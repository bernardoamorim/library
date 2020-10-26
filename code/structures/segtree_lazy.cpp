// SegTree with Lazy Propagation
//
// lazy_segtree<seg type, lazy type>
// you have to change things inside seg anyway, but I think this way is better
// 
// Sum of range implement (lazy_segtree<pair<ll,int>, int>)
//
// Assuming ap, merge and comp are O(1)
// build - O(n)
// query - O(log(n))
// update - O(log(n))

template<typename T,typename U> struct lazy_segtree {
	int sz;
	T s_id = {0,0};
	U l_id = 0;
	vector<T> seg, v;
	vector<U> lazy;
	
	T merge(T s1, T s2) { return {s1.first + s2.first, s1.second + s2.second}; }
	T apply(U x, T s) { return {s.first + x * s.second, s.second}; }
	U compose(U x1, U x2) { return x1 + x2; }
	
	T build(int p, int l, int r) {
		if (l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = merge(build(2*p,l,m), build(2*p+1,m+1,r));
	}
	void prop(int p) {
		U x = lazy[p];
		if(x == l_id) return;
		seg[2*p] = apply(x,seg[2*p]);
		seg[2*p+1] = apply(x,seg[2*p+1]);
		lazy[2*p] = compose(x,lazy[2*p]);
		lazy[2*p+1] = compose(x,lazy[2*p+1]);
		lazy[p] = l_id;
	}
	T query(int s, int e, int p, int l, int r) {
		if(e < l or r < s) return s_id;
		if(s <= l and r <= e) return seg[p];
		prop(p); 
		int m = (l+r)/2;
		return merge(query(s,e,2*p,l,m), query(s,e,2*p+1,m+1,r));
	}
	T update(int s, int e, U x, int p, int l, int r) {
		if(e < l or r < s) return seg[p];
		if(s <= l and r <= e) {
			lazy[p] = compose(x, lazy[p]);
			return seg[p] = apply(x, seg[p]);
		}
		prop(p); 
		int m = (l+r)/2;
		return seg[p] = merge(update(s,e,x,2*p,l,m), update(s,e,x,2*p+1,m+1,r));
	}

	lazy_segtree(int sz_, vector<T> v_={}) : sz(sz_), seg(4*sz_, s_id), lazy(4*sz_, l_id) {
		v = (v_.empty() ? vector<T>(sz, {0,1}) : v_); // be careful with initial value
		build(1,0,sz-1);
	}
	T update(int s, int e, U x) { return update(s, e, x, 1, 0, sz-1); }
	T query(int s, int e) { return query(s, e, 1, 0, sz-1); }
};

// TO ADD LEFT AND RIGHT
