// Suffix Tree
//
// tree is an adjancency list of the suffix tree, root is at position 0
//
// Edge.l and Edge.r represent the range of the suffix-array which has the substrings that end on
// Edge and on the subtree of Edge.to
//
// Edge.szl and Edge.szr represent the range of prefixes that end in Edge
//
// Complexity: O(|s|.log(|s|)), can be linear using linear suffix-array and linear RMQ

struct SuffixTree {
	struct Edge {
		int l, r, szl, szr, to;
		Edge(int l_, int r_, int szl_, int szr_, int to_) : 
			l(l_), r(r_), szl(szl_), szr(szr_), to(to_) {}
	};

	string s;
	int n;
	vector<int> sa, vlcp;
	vector<vector<Edge>> tree;
	SparseTable<int> rmq;

	void dfs(int l, int r, int pref, int id) { // Pre-order DFS
		if (sa[l] + pref == n) {
			if (l == r) {
				int npref = n - sa[l], nid = tree.size();
				tree.push_back({});
				tree[id].emplace_back(l, r, pref + 1, npref, nid);
				return;
			}
			else l++;
		}
		while (l <= r) {
			int i = l != r ? rmq.index_query(l, r - 1) : -1;
			if (i == -1 or vlcp[i] != pref) i = r;

			int npref = l != i ? rmq.query(l, i - 1) : n - sa[l], nid = tree.size();
			tree.push_back({});
			tree[id].emplace_back(l, i, pref + 1, npref, nid);

			dfs(l, i, npref, nid);
			l = i + 1;
		}
	}
	void build(const string& s_) {
		s = s_, n = s.size(), sa = suffix_array(s), vlcp = lcp(s, sa);		
		rmq.build(vlcp);
		tree = {{}};
		dfs(0, n - 1, 0, 0);
	}
};
