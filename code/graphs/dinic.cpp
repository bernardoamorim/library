// Dinic
// 
// max_flow(s,t) computes maximumm flow from s to t (do not call more than once)
// min_cut(s,t) returns {max_flow,min_cut}, where in min_cut edges are indexed from
// the order they are added
//
// O(min(m * max_flow, n^2 m)), if graph has capacities 1 O(sqrt(n)*m)

struct dinic {
	struct edge { int to, id, cap; }; // id % 2 (0 if original, 1 if residual)
	vector<vector<edge>> g;
	vector<int> flow, lvl, it;
	
	int dfs(int v, int flow_aug, int t) {
		if(v == t) return flow_aug;
		for(int& i = it[v]; i < g[v].size(); i++) {
			edge e = g[v][i];
			int left = e.cap - flow[e.id];
			if(lvl[e.to] != lvl[v] + 1 or !left) continue;
			int aug = dfs(e.to, min(flow_aug, left), t);
			if(!aug) continue;
			flow[e.id] += aug, flow[e.id^1] -= aug;
			return aug;
		}
		return 0;
	}
	bool bfs(int s, int t) {
		fill(lvl.begin(), lvl.end(), -1); lvl[s] = 0;
		queue<int> q; q.push(s);
		while(q.size()) {
			int u = q.front(); q.pop();
			for(auto e : g[u]) { 
				if(e.cap-flow[e.id] > 0 and lvl[e.to] == -1)
					lvl[e.to] = lvl[u] + 1, q.push(e.to);
			}
		}
		return lvl[t] != -1;
	}
	dinic(int sz) : g(sz), lvl(sz), it(sz) {}
	void add_edge(int u, int v, int cap) {
		g[u].push_back(edge{v, (int)flow.size(), cap}); flow.push_back(0);
		g[v].push_back(edge{u, (int)flow.size(), cap}); flow.push_back(cap);
	}
	int max_flow(int s, int t) {
		int max_flow = 0;
		while(bfs(s,t)) {
			fill(it.begin(), it.end(), 0);
			while(int aug = dfs(s,INF,t)) max_flow += aug;
		}
		return max_flow;	
	}
	pair<int,vector<int>> min_cut(int s, int t) {
		int maxflow = max_flow(s,t);
		vector<int> part(g.size(),0), mincut;
		function<void(int)> find_aug = [&] (int u) {
			for(auto e : g[u]) if(!part[e.to] and e.cap > flow[e.id])
				part[e.to] = 1, find_aug(e.to);
		};
		part[s] = 1, find_aug(s);
		for(int u=0; u < g.size(); u++) for(auto e : g[u]) 
			if(part[u] and !part[e.to] and !(e.id & 1)) mincut.push_back(e.id/2);
		return {maxflow, mincut};
	}
};
