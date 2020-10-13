// Kruskal
//
// Generates and retuns a MST (minimum spanning tree)
//  and its cost from the edges vector
//
// O(m log(m) + m a(m))

typedef tuple<int,int,int> t3;

vector<t3> edg; // {weight,[x,y]}

// struct dsu()

pair<ll,vector<t3>> kruskal(int n) {
	dsu comps(n);
	sort(edg.begin(), edg.end());
	
	ll cost = 0;
	vector<t3> mst;
	for(auto [w,x,y] : edg) if(comps.find(x) != comps.find(y)) {
		mst.push_back({w,x,y});
		cost += w;
		comps.unite(x,y);
	}
	return {cost,mst};
}
