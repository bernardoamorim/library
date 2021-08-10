// Sparse Table
//
// Can do idepotent operations (mainly min and max)
//
// op(i, j) should return the index you want when receiving based on indexes i and j of v
// in the example, op returns the position of the leftmost min
//
// K >= floor(log2(n) + 1)
//
// Complexity:
// build: O(|v|.log(|v|))
// query: O(1)
// memory: O(|v|.log(|v|))

template<typename T, int k = 25> struct SparseTable {
	vector<T> v;
	vector<int> log, table[k];

	inline int op(int i, int j) { return v[i] <= v[j] ? i : j; }

	void build(const vector<T>& v_) {
		int n = v_.size();
		v = v_, log.assign(n + 1, 0);
		for (int i = 0; i < k; i++) table[i].resize(n);
		for (int i = 2; i <= n; i++) log[i] = 1 + log[i / 2];
		iota(begin(table[0]), end(table[0]), 0);
		
		for (int p = 1; p < k; p++) for (int i = 0; i + (1 << p) <= n; i++)
			table[p][i] = op(table[p-1][i], table[p-1][i + (1 << (p - 1))]);
	}
	int index_query(int l, int r) {
		int p = log[r - l + 1];
		return op(table[p][l], table[p][r - (1 << p) + 1]);
	}
	T query(int l, int r) { return v[index_query(l, r)]; }
};
