// BFS
// Acha distância até os pontos e os componentes conexos

// Complexidade: O(v+e)


int d[MAX];

void bfs(int x) {
	queue<int> q;
	memset(d, -1, sizeof d);	
	d[x] = 0;
	q.push(x);
	
	while (!q.empty()) {
		int s = q.front(); q.pop();
		for (auto u : g[s]) {
			if (d[x] != -1) continue;
			d[u] = d[s]+1;
			q.push(u);
		}
	}
}
