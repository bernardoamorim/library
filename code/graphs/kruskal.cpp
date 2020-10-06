// Kruskal
//
// Generates and retuns an MST and its cost from the edges vector
// do grafo
//
// O(m log(m) + m a(m))

typedef tuple<int,int,int> t3;

vector<t3> edg; // {weight,[x,y]}

// DSU in O(a(n))
void dsu_build();
int find(int a);
void unite(int a, int b);

pair<ll,vector<t3>> kruskal(int n) {
	dsu_build(n);
	sort(edg.begin(), edg.end());
	
	ll cost = 0;
	vector<t3> mst;
	for(auto [w,x,y] : edg) if(find(x) != find(y)) {
		mst.push_back({w,x,y});
		cost += w;
		unite(x,y);
	}
	return {cost,mst};
}
