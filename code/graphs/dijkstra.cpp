// Dijkstra
//
// Finds the distance from s to every vertex
// If in the end d[v] = LINF, then s does not reach v
//
// O(m.log(n))

vector<ll> d(MAX);
vector<pair<int,int>> g[MAX]; // {neighbour, edge weight}
int n;
 
void dijkstra(int s) {
	fill(all(d), LINF);
	priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
	pq.emplace(d[s] = 0, s);
 
	while(not pq.empty()) {
		auto [dd, v] = pq.top(); pq.pop();
		if(dd > d[v]) continue;
		
		for(auto [u, w] : g[v]) if(d[v] + w < d[u])
			pq.emplace(d[u] = d[v] + w, u);
	}
}
