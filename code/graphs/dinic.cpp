// Dinic
// 
// Computes the maximum flow from s to t (do not call more than once)
//
// O(min(m * max_flow, n^2 m))
// Graph with capacities 1 -> O(sqrt(n)*m)

class dinic {
private:
	struct edge {
		int to, id, cap; // id is even if original and odd if residual
		edge(int to_, int id_, int cap_) : to(to_), id(id_), cap(cap_) {}
	};
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
	int bfs(int s, int t) {
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
public:
	dinic(int sz) : g(sz), lvl(sz), it(sz) {}

	void add_edge(int u, int v, int cap) {
		g[u].push_back(edge(v, flow.size(), cap)); flow.push_back(0);
		g[v].push_back(edge(u, flow.size(), cap)); flow.push_back(cap);
	}
	int max_flow(int s, int t) {
		int max_flow = 0;
		while(bfs(s,t)) {
			fill(it.begin(), it.end(), 0);
			while(int aug = dfs(s,INF,t)) max_flow += aug;
		}
		return max_flow;	
	}
};
