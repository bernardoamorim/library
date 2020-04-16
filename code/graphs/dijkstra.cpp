// dijkstra
//
// Dijkstra
//
// encontra menor distancia de a
// para todos os vertices
// se ao final do algoritmo d[i] = INF,
// entao a nao alcanca i
//
// O(m log(n))

int n;
vector<vector<int> > g(MAX);
vector<vector<int> > w(MAX); // peso das arestas
int d[MAX];

void dijkstra(int x) {
	for (int i = 0; i < n; i++) d[i] = INF;
	d[x] = 0;
	priority_queue<ii> q;
	q.push({0, x});

	while (!q.empty()) {
		int u = q.top().s, dist = -q.top().f;
		q.pop();
		if (dist > d[u]) continue;

		for (int i = 0; i < (int) g[u].size(); i++) {
			int v = g[u][i];
			if (d[v] > d[u] + w[u][i]) {
				d[v] = d[u] + w[u][i];
				q.push({-d[v], v});
			}
		}
	}
}
