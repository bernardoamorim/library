// DSU
//
// Unites sets and finds its class
//
// O(a(n)) ~= O(1)

int id[MAX], sz[MAX];

void dsu_build(int n) { for(int i=0; i<n; i++) sz[i] = 1, id[i] = i; }

int find(int a) { return id[a] = a == id[a] ? a : find(id[a]); }

void unite(int a, int b) {
	a = find(a), b = find(b);
	if(a == b) return;
	if(sz[a] < sz[b]) swap(a,b);

	sz[a] += sz[b];
	id[b] = a;
}
