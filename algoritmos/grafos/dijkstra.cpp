// dijkstra
//
// encontra menor distancia de x
// para todos os vertices
// se ao final do algoritmo d[i] = INF,
// entao a nao alcanca i
//
// O(m log(n))

vector<vector<pii> > grafo;
vector<int> dist;
vector<bool> vis;

void dijkstra(int x) {
	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
		vis[i] = false;
	}	

	dist[x] = 0;
	q.push({0,x});

	while (!q.empty()) {
		int a = q.top().second; q.pop();

		if (vis[a]) continue;
		vis[a] = true;

		for (auto u : grafo[a]) {
			int b = u.first, w = u.second;

			if (dist[a]+w < dist[b]) {
				dist[b] = dist[a]+w;
				q.push({-dist[b],b}); // distancia negativa para queue
			}
		}
	}
}
