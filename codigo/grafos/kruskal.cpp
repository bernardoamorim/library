// Kruskal

// Gera AGM a partir do vetor de arestas ar
// e retorna seu peso w

// Usa DSU

// Complexidade O(m log(n))

int n; // n de vertices

vector<pair<int,ii> > > ar;
vector<int> par;
vector<int> sz;

void build();	
int find(int v);
void une(int a, int b);

int kruskal() {
	
	int w = 0;

	build();

	sort(ar.begin(), ar.end());

	for(auto x : ar) {
		int u = ar.ss.ff, v = ar.ss.ss;
		if(find(u) != find(v)) {
			w += x.ff;
			une(u,v);
		}
	}
	return w;
}
