// Splay Tree
//
// Works like a set/map, thus no repeated keys
// To add more informations, make sure that update() is working well
// 
// Complexity:
// All functions, beside size() and rotate() (O(1)), cost O(log(|splay|)) amortized.
// Be careful with updates when adding more informations to a node
// Do not copy the structure

template<typename T> struct SplayTree {
	struct Node {
		T key;
		int sz;
		Node *p, *ch[2];
		Node (T key_, Node* p_ = nullptr) : key(key_), sz(1), p(p_) {
			ch[0] = ch[1] = nullptr;
		}
		void update() {
			sz = 1;
			if (ch[0]) sz += ch[0]->sz;
			if (ch[1]) sz += ch[1]->sz;
		}
	};

	Node *root;

	SplayTree() : root(nullptr) {}

	~SplayTree() {
		queue<Node*> q;
		q.push(root);
		while (not q.empty()) {
			if (q.front()) q.push(q.front()->ch[0]), q.push(q.front()->ch[1]);
			delete q.front();
			q.pop();
		}
	}

	int size() { return root ? root->sz : 0; }
	
	int count (T key) {
		Node *v = lower_bound(key);
		return v and v->key == key;
	}

	void rotate(Node *v) {
		Node *p = v->p, *gp = p->p;
		bool r_rot = p->ch[0] == v;
		Node *u = v->ch[r_rot];
		if (u) u->p = p;
		if (gp) gp->ch[0] == p ? gp->ch[0] = v : gp->ch[1] = v;
		v->p = p->p, p->p = v, v->ch[r_rot] = p, p->ch[!r_rot] = u;
		p->update(), v->update();
	}

	void splay(Node *v) {
		while (v->p) {
			Node *p = v->p, *gp = p->p;
			if (not gp) rotate(v);
			else if ((gp->ch[0] == p) ^ (p->ch[0] == v)) rotate(v), rotate(v);
			else rotate(p), rotate(v);
		}
		root = v;
	}
	
	void insert(T key) {
		if (not root) {
			root = new Node(key);
			return;
		}
		Node *v = root;
		while (v) {
			if (v->key == key) {
				splay(v);
				break;
			}
			bool r = v->key < key;
			if (not v->ch[r]) {
				v->ch[r] = new Node(key, v);
				v->update();
				break;
			}
			else v = v->ch[r];
		}
		splay(v);
	}

	void erase(T key) {
		if (not count(key)) return;
		Node *v = root;
		if (!v->ch[0]) {
			root = v->ch[1];
			if (root) root->p = nullptr;
		}
		else {
			Node *u = v->ch[0];
			root = v->ch[0], root->p = nullptr;
			while (u->ch[1]) u = u->ch[1];
			splay(u);
			root->ch[1] = v->ch[1];
			if (v->ch[1]) v->ch[1]->p = root;
			root->update();
		}
		delete v;
	}

	Node* lower_bound(T key) {
		Node *v = root, *v_best = nullptr, *last = nullptr;
		while (v) {
			last = v;
			if (v->key < key) v = v->ch[1];
			else if (v->key == key) {
				v_best = v;
				break;
			}
			else {
				if (not v_best or v->key < v_best->key) 
					v_best = v;
				v = v->ch[0];
			}
		}
		if (last) splay(last);
		if (v_best) splay(v_best);
		return v_best;
	}

	int order_of_key (T key) {
		if (not lower_bound(key)) return root ? root->sz : 0;
		return root->ch[0] ? root->ch[0]->sz : 0;
	}

	Node* find_by_order (int k) {
		if (size() <= k) return nullptr;
		Node *v = root;
		while (true) {
			int lsz = (v->ch[0] ? v->ch[0]->sz : 0);
			if (lsz > k) v = v->ch[0];
			else {
				k -= lsz;
				if (k == 0) break;
				k--, v = v->ch[1];	
			}
		}
		splay(v);
		return v;
	}
};
