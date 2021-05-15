// Sparse Table
//
// Can do idepotent operations (mainly min and max)
//
// build(v) builds a sparse table on v
// query(l, r) returns the INDEX of op
// op(i, j) should return the index you want when receiving based on indexes i and j of v
// in the example, op returns the position of the leftmost min
//
// Complexity:
// build: O(|v|.log(|v|))
// query: O(1)
// memory: O(|v|.log(|v|))

template<typename T>
struct SparseTable {
	vector<vector<T>> table;
	vector<T> v;
	vector<int> log;
	int n, n2;

	inline int op(int i, int j) { return v[i] <= v[j] ? i : j; }
	
	void build(const vector<T>& v_) {
		n = v_.size(), n2 = floor(log2(n)) + 1;
		v = v_, log = vector<int>(n + 1), table = vector(n, vector<T>(n2));

		for (int i = 1; i <= n; i++) 
			log[i] = __builtin_clz(1) - __builtin_clz(i);
		for (int i = 0; i < n; i++)
			table[i][0] = i; // change to v[i] to use values instead of indices

		for (int p = 1; p < n2; p++)
			for (int i = 0; i + (1 << p) <= n; i++)
				table[i][p] = op(table[i][p-1], table[i + (1 << (p - 1))][p-1]);
	}
	int query(int l, int r) {
		int p = log[r - l + 1];
		return op(table[l][p], table[r - (1 << p) + 1][p]);
	}
};
