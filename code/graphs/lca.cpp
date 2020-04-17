// LCA with binary lifting
//
// Assumes a vertice is its own acestor
// thus if a is ancestor of b, lca(a,b) = a
// MAX2 = ceil(log(MAX))
//
// Time complexities:
// build - O(n log(n))
// lca - O(log(n))

vector<vector<int> > g(MAX);
int n, p;
int par[MAX2][MAX];
int in[MAX], out[MAX];

void dfs(int k) {
	in[k] = p++;
	for (auto u : g[k]) {
		if (in[u] == -1) {
			par[0][u] = k;
			dfs(u);
		}
	}
	out[k] = p++;
}

void build(int root) {
	for (int i = 0; i < n; i++) par[0][i] = i;
	p = 0; memset(in, -1, sizeof in);
	dfs(root);

	// parents dp
	for (int k = 1; k < MAX2; k++) for (int i = 0; i < n; i++)
		par[k][i] = par[k - 1][par[k - 1][i]];
}

bool anc(int a, int b) { // if a is ancestor of b
	return in[a] <= in[b] and out[a] >= out[b];
}

int lca(int a, int b) {
	if (anc(a, b)) return a;
	if (anc(b, a)) return b;

	// lifts a
	for (int k = MAX2 - 1; k >= 0; k--)
		if (!anc(par[k][a], b)) a = par[k][a];

	return par[0][a];
}
