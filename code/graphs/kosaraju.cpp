// Kosaraju
//
// Finds the SCCs of a graph and returns its number.
// In comp[u] there will be a vertex from the same SCC as u
//
// O(n + m)
 
vector<int> g[MAX], gt[MAX]; // graph, transposed graph
int vis[MAX], comp[MAX];
 
int kosaraju(int n) {
 
    vector<int> st;
    function<void(int)> dfs = [&] (int v) {
        vis[v] = 1;
        for(auto u : g[v]) if(!vis[u]) dfs(u);
        st.push_back(v);
    };
 
    function<void(int,int)> dfst = [&] (int v, int c) {
        vis[v] = 1, comp[v] = c;
        for(auto u : gt[v]) if(!vis[u]) dfst(u,c);
    };
 
    fill(vis,vis+n,0);
    for(int i=0; i<n; i++) if(!vis[i]) dfs(i);
    
    fill(vis,vis+n,0);
    int ncomps = 0;
    while(st.size()) {
        int u = st.top(); st.pop();
        if(!vis[u]) dfst(u,u), ncomps++;
    }
    return ncomps;
}
