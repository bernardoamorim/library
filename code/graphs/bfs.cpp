// BFS
// Finds the distances and the connected componets
//
// Complexity: 
// Time: O(v+e)

int d[MAX];
vector<vector<int>> g;

void bfs(int x) {
	memset(d, -1, sizeof d);	
	queue<int> q;

	d[x] = 0;	
	q.push(x);
	
	while(!q.empty()) {
		int s = q.front(); q.pop();
		for(auto u : g[s]) if(d[u] == -1) {
			d[u] = d[s]+1;
			q.push(u);
		}
	}
}
