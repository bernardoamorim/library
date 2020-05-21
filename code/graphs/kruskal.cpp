// Kruskal
//
// Generates MST from the edges vector ed
// and returns its total weigh w
//
// Uses DSU

// Time complexity: O(m log(n))

int n; // n of nodees

vector<pair<int,ii> > > edg;
vector<int> par;
vector<int> sz;

void build();	
int find(int v);
void unite(int a, int b);

int kruskal() {
	int w = 0;
	build();
	sort(edg.begin(), edg.end());

	for(auto x : edg) {
		int u = edg.s.f, v = edg.s.s;
		if(find(u) != find(v)) {
			w += x.f;
			unite(u,v);
		}
	}
	return w;
}
