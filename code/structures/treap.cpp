// Implicit Treap
//
// Works as a better vector, supporting reversion, insertion, merging, range queries, etc...
// 
// Every function returns the pointer to the new root, be careful
//
// In this case, to update a subtree, grab its root (using split) and change its lazy/rev value
//
// Be VERY careful when modifying this code, specially the lazy propagation 
// and remember that the node in the middle also holds a value
//
// Complexity:
// All operations have complexity O(|Treap|) with high probability

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

struct Treap {
	int sz, prior;
	Treap *l, *r;
	int val; // be careful when changing the type
	bool rev;
	ll lazy, sum;
	Treap (int val_) : sz(1), prior(rng()), l(nullptr), r(nullptr), val(val_), rev(0), lazy(0), sum(val) {}
	
	void prop() {
		if (rev) {
			swap(l, r);
			if (l) l->rev ^= 1;
			if (r) r->rev ^= 1;
		}
		if (lazy != 0) {
			val += lazy, sum += lazy * sz;
			if (l) l->lazy += lazy;
			if (r) r->lazy += lazy;
		}
		rev = false, lazy = 0;
	}
	
	void recalc() {
		sz = 1, sum = val;
		if (l) l->prop(), sz += l->sz, sum += l->sum;
		if (r) r->prop(), sz += r->sz, sum += r->sum;
		lazy = 0;
	}
};

int size(Treap *t) { return t ? t->sz : 0; }

Treap* merge(Treap* tl, Treap* tr) {
	if (not tl or not tr) return tl ? tl : tr;
	tl->prop(), tr->prop();
	if (tl->prior > tr->prior) {
		tl->r = merge(tl->r, tr), tl->recalc();
		return tl;
	}
	else {
		tr->l = merge(tl, tr->l), tr->recalc();
		return tr;
	}
}

// k will be the size of the left (if possible, otherwise I don't know)
pair<Treap*, Treap*> index_split(Treap* t, int k) { 
	if (not t) return {nullptr, nullptr};
	t->prop();
	if (k <= size(t->l)) {
		auto [tll, tlr] = index_split(t->l, k);
		t->l = tlr, t->recalc();
		return {tll, t};
	}
	else {
		auto [trl, trr] = index_split(t->r, k - (size(t->l) + 1));
		t->r = trl, t->recalc();
		return {t, trr};
	}
}

Treap* insert(Treap* t, int val, int pos) {
	auto [tl, tr] = index_split(t, pos);
	Treap *nt = new Treap(val);
	return merge(tl, merge(nt, tr));
}
