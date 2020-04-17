// DSU
//
// Unites sets and finds its class
//
// Time complexity: O(a(n)) ~= O(1)

int n; // n elements

int par[n], sz[n];

void build() {
	for(int i=0; i<n; i++) {
		par[i] = i;
		sz[i] = 1;
	}
}

int find(int v) {
	if(par[v] == v) return v;
	else return par[v] = find(par[v]);
}

void unite(int a, int b) {
	a = find(a);
	b = find(b);

	if(a != b) {
		if(sz[a] < sz[b]) swap(a,b);

		par[b] = a;
		sz[a] += sz[b];
	}
}
