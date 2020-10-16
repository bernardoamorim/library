// SegTree with Lazy Propagation
//
// Made to be modified, time will tell if doing this way is worth it
//
// Assuming ap, merge and comp are O(1)
// build - O(n)
// query - O(log(n))
// update - O(log(n))

// <seg_type, s_id, merge, lz_type, l_id, apply_lz_to_seg, comp_lz>

template<class S,S (*s_id)(),S (*merge)(S,S),class L,L (*l_id)(),S (*ap)(L,S),L (*comp)(L,L)>
class lazy_segtree {
public:
	int sz;
	vector<S> seg;
	vector<L> lz;
	S build(vector<S>& v, int p, int l, int r) {
		if (l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = merge(build(v,2*p,l,m),build(v,2*p+1,m+1,r));
	}
	void prop(int p) {
		if(lz[p] == l_id()) return;
		L l = lz[p];
		seg[2*p] = ap(l,seg[2*p]), seg[2*p+1] = ap(l,seg[2*p+1]);
		lz[2*p] = comp(l,lz[2*p]), lz[2*p+1] = comp(l,lz[2*p+1]);
		lz[p] = l_id();
	}
	S query(int s, int e, int p, int l, int r) {
		if(e < l or r < s) return s_id();
		if(s <= l and r <= e) return seg[p];
		prop(p); int m = (l+r)/2;
		return merge(query(s,e,2*p,l,m), query(s,e,2*p+1,m+1,r));
	}
	S update(int s, int e, L x, int p, int l, int r) {
		if(e < l or r < s) return seg[p];
		if(s <= l and r <= e) {
			lz[p] = comp(x, lz[p]);
			return seg[p] = ap(x, seg[p]);
		}
		prop(p); int m = (l+r)/2;
		return seg[p] = merge(update(s,e,x,2*p,l,m), update(s,e,x,2*p+1,m+1,r));
	}
public:
	S update(int s, int e, L x) { return update(s, e, x, 1, 0, sz-1); }
	S query(int s, int e) { return query(s, e, 1, 0, sz-1); }
	lazy_segtree() : lazy_segtree(0) {}
	lazy_segtree(int sz_) : lazy_segtree(vector<S>(sz_)) {}
	lazy_segtree(vector<S> v) {
		sz = v.size();
		seg = vector<S>(4*sz, s_id()); 
		lz = vector<L>(4*sz, l_id());
		build(v,1,0,sz-1);
	}
};

// Example:
// query: sum [a, b]
// update: summates x im each element in [a, b]

// Seg type (with empty constructor)
struct node { ll sum = 0, sz = 1; };

// Seg type identity element
node s_id() { return node{0,0};}

// Merge two segs
node merge(node l, node r) { return node{l.sum+r.sum, l.sz+r.sz}; };

// Update (lazy) type
// ll

// Update (lazy) identity element
ll l_id() { return 0; }

// Apply update to segtree
node ap(ll v, node p) { return node{p.sum + v*p.sz, p.sz}; };

// Compose two updates (left is the newer if it matters)
ll comp(ll l, ll r) { return l+r; };

// TO ADD LEFT AND RIGHT
