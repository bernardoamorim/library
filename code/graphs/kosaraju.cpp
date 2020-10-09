// Kosaraju
//
// Finds the SCCs of a graph and returns its number.
// In comp[u] there will be a vertex from the same SCC as u
//
// O(n + m)
 
vector<int> g[MAX], gt[MAX]; // graph, transposed graph
 
pair<int,vector<int>> kosaraju(int n) {

    vector<int> vis(n), comp(n), to_look(n);
	int it = n-1;
 
    function<void(int)> dfs = [&] (int v) {
        vis[v] = 1;
        for(int u : g[v]) if(!vis[u]) dfs(u);
        to_look[it--] = v;
    };
 
    function<void(int,int)> dfst = [&] (int v, int c) {
        vis[v] = 1, comp[v] = c;
        for(int u : gt[v]) if(!vis[u]) dfst(u,c);
    };

    for(int i=0; i<n; i++) if(!vis[i]) dfs(i);
    
    int ncomps = 0;
    fill(vis.begin(),vis.end(),0);
    for(int u : to_look) if(!vis[u])
		dfst(u,u), ncomps++;
 
    return {ncomps, comp};
}
