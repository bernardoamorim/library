// Dinic
// 
// Computes the maximum flow from s to t (do not call more than once)
//
// O(min(m * max_flow, n^2 m))
// Graph with capacities 1 -> O(sqrt(n)*m)

struct dinic { 
	struct edge {
		// idx is even if original and odd if residual
		int to, idx, cap;
		edge (int to_, int idx_, int cap_) : 
			to(to_), idx(idx_), cap(cap_) {}
	};

	int sz;
	vector<vector<edge>> g;
	vector<int> edg_flow, level, iter; 

	dinic (int sz_) : sz(sz_), g(sz_), level(sz_), iter(sz_) {}

	void add_edge(int u, int v, int cap) {
		g[u].push_back(edge(v, edg_flow.size(), cap));
		edg_flow.push_back(0);
		g[v].push_back(edge(u, edg_flow.size(), cap));
		edg_flow.push_back(cap);
	}

	int max_flow(int s, int t) {

		function<int(int,int)> dfs = [&] (int v, int flow_aug) {
			if(v == t or flow_aug == 0) return flow_aug;
			for(int& i = iter[v]; i < g[v].size(); i++) {
				edge e = g[v][i];
				int left = e.cap - edg_flow[e.idx], pushed = 0;
				if(level[e.to] == level[v] + 1 and left)
					pushed = dfs(e.to, min(flow_aug, left));
				
				if(pushed > 0) {
					edg_flow[e.idx] += pushed;
					edg_flow[e.idx^1] -= pushed;
					return pushed;
				}
			}
			return 0;
		};

		auto bfs = [&] () {
			fill(level.begin(), level.end(), -1);
			queue<int> q;
			level[s] = 0;
			q.push(s);

			while(q.size()) {
				int u = q.front(); q.pop();
				for(auto e : g[u]) if(e.cap - edg_flow[e.idx] > 0 and level[e.to] == -1) {
					level[e.to] = level[u] + 1;
					q.push(e.to);
				}
			}
			return level[t] != -1;
		};

		int max_flow = 0;
		while(bfs()) {
			fill(iter.begin(), iter.end(), 0);
			while(true) {
				int aug = dfs(s,INF);
				if(aug == 0) break;
				max_flow += aug;
			}
		}
		return max_flow;		
	}
};
