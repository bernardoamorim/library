// Dijkstra
//
// Finds the smaller distance from x to any vertice
// in a directed graph
// If you need the distance from any vertice to x,
// reverse the edges
// if at the end d[i] = INF,
// so x doesn'r reach i
//
// Time complexity: O(m log(n))

int n;
vector<vector<int> > g(MAX);
vector<vector<int> > w(MAX); // weigh
int d[MAX];

void dijkstra(int x) {
	for (int i = 0; i < n; i++) d[i] = INF;
	d[x] = 0;
	priority_queue<ii> q;
	q.push({0, x});

	while (!q.empty()) {
		auto [dist,u] = q.top(); dist*=-1; q.pop();
		
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
