// DSU

// Une conjuntos e acha sua classe

// Complexidades:
// O(a(n)) == O(pouquinho)

int n; // n elementos

vector<int> par;
vector<int> sz;

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

void une(int a, int b) {
	a = find(a);
	b = find(b);

	if(a != b) {
		if(sz[a] < sz[b]) swap(a,b);

		par[b] = a;
		sz[a] += sz[b];
	}
}
