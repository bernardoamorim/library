// Dijkstra
//
// Finds the distance from x to every vertex
// If in the end d[i] = INF, then x does not reach i
//
// O(m log(n))

int d[MAX];
vector<pair<int,int>> g[MAX]; // {neighbout, edge weight}

int n;
 
void dijkstra(int x) {
	for(int i=0; i < n; i++) d[i] = INF;
	d[x] = 0;
	priority_queue<pair<int,int>> pq;
	pq.push({0,x});
 
	while(pq.size()) {
		auto [ndist,u] = pq.top(); pq.pop();
		if(-ndist > d[u]) continue;
 
		for(auto [idx,w] : g[u]) if(d[idx] > d[u] + w) {
			d[idx] = d[u] + w;
			pq.push({-d[idx], idx});
		}
	}
}
