// DFS
// Encontra componentes conexos

// Complexidade: O(v+e)

void dfs(int s) {
	if (vis[s]) return;
	vis[s] = true;
	for (auto u: adj[s]) {
		dfs(u);
	}
}
