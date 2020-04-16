// DFS
// Encontra componentes conexos

// Complexidade: O(v+e)

void dfs(int s) {
	if (v[s]) return;
	v[s] = true;
	for (auto u: adj[s]) dfs(u);
}
