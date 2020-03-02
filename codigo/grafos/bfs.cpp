// BFS
// Acha distância até os pontos e os componentes conexos

// Complexidade: O(v+e)

queue<int> q;
bool vis[N];
int dist[N];

void bfs(int x) {
	vis[x] = true;
	dist[x] = 0;
	q.push(x);
	
	while (!q.empty()) {
		int s = q.front(); q.pop();
		// process node s
		for (auto u : adj[s]) {
			if (vis[u]) continue;
			vis[u] = true;
			dist[u] = dist[s]+1;
			q.push(u);
		}
	}
}
