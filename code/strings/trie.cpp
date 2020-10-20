// Trie
// <alphabet size, initial char i.e. 'a' for lowercase letters
//
// insert, erase, count and find: O(|s|)
// prefix(s) returns all strings that have s as prefix excluding s itself

template<int sigma, char norm> struct trie {
	vector<vector<int>> tree;
	vector<int> end;

	trie() : tree(1,vector<int>(sigma,-1)), end(1,0) {}

	void insert(string s) {
		int node = 0;
		for(auto c : s) {
			int& nxt = tree[node][c-norm];
			if(nxt == -1) {
				nxt = tree.size();
				tree.push_back(vector<int>(sigma,-1));
				end.push_back(0);
			}
			node = nxt;
		}
		end[node]++;
	}

	int find(string s) {
		int node = 0;
		for(auto c : s) {
			if(tree[node][c-norm] == -1) return -1;
			node = tree[node][c-norm];
		}
		return node;
	}

	int count(string s) {
		int node = find(s);
		return node == -1 ? 0 : end[node];
	}
	
	void erase(string s) {
		int snode = find(s);
		if(snode != -1) end[snode]--;
	}

	vector<string> prefix(string s) {
		vector<string> ret;	
		int snode = find(s);
		function<void(int)> dfs = [&] (int tnode) {
			if(end[tnode] and tnode != snode) ret.push_back(s);
			for(int i = 0; i < sigma; i++) if(tree[tnode][i] != -1) {
				s += norm + i;
				dfs(tree[tnode][i]);
				s.pop_back();
			}
		};
		if(snode != -1) dfs(snode);
		return ret;
	}
};
