// Sparse Table
//
// Can do idepotent operations (mainly min and max)
//
// build(v) builds a sparse table on v
// query(l, r) returns the INDEX of op
// op(i, j) should return the index you want when receiving based on indexes i and j of v
// in the example, op returns the position of the leftmost min
//
// K >= floor(log2(n) + 1)
//
// Complexity:
// build: O(|v|.log(|v|))
// query: O(1)
// memory: O(|v|.log(|v|))

template<typename T, int k = 25>
struct SparseTable {
	vector<T> v, table[k];
	vector<int> log;

	inline int op(int i, int j) { return v[i] <= v[j] ? i : j; }
	
	void build(const vector<T>& v_) {
		int n = v_.size(), n2 = floor(log2(n)) + 1;
		v = v_, log = vector<int>(n + 1);
		assert(k >= n2);
		for (int i = 0; i < n2; i++) table[i] = vector<T>(n);

		for (int i = 1; i <= n; i++) log[i] = __builtin_clz(1) - __builtin_clz(i);
		for (int i = 0; i < n; i++) table[0][i] = i; // change to v[i] to use values instead of indices

		for (int p = 1; p < n2; p++)
			for (int i = 0; i + (1 << p) <= n; i++)
				table[p][i] = op(table[p-1][i], table[p-1][i + (1 << (p - 1))]);
	}
	int query(int l, int r) {
		int p = log[r - l + 1];
		return op(table[p][l], table[p][r - (1 << p) + 1]);
	}
};
