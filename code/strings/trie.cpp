// Trie
// trie T(alphabet size, initial char (i.e.'a' for lowercase letters))
// be careful, alphabet size is the size from norm to the last char used
//
// insert, erase, count and find: O(|s|)
// prefix(s) returns all strings that have s as prefix excluding s itself

struct trie {
	vector<vector<int>> to;
	vector<int> end;
	int sigma; char norm;
	trie(int sigma_, char norm_) : sigma(sigma_), norm(norm_) {
		to = {vector<int>(sigma,-1)};
		end = {0};
	}
	void insert(string s) {
		int v = 0;
		for(auto c : s) {
			int& nxt = to[v][c-norm];
			if(nxt == -1) {
				nxt = to.size();
				to.push_back(vector<int>(sigma,-1));
				end.push_back(0);
			}
			v = nxt;
		}
		end[v]++;
	}
	int find(string s) {
		int v = 0;
		for(auto c : s) {
			if(to[v][c-norm] == -1) return -1;
			v = to[v][c-norm];
		}
		return v;
	}
	int count(string s) {
		int v = find(s);
		return v == -1 ? 0 : end[v];
	}
	void erase(string s) {
		int vs = find(s);
		if(vs != -1) end[vs]--;
	}
	vector<string> prefix(string s) {
		vector<string> ret;	
		int vs = find(s);
		function<void(int)> dfs = [&] (int vt) {
			if(end[vt] and vt != vs) ret.push_back(s);
			for(int c = 0; c < sigma; c++) if(to[vt][c] != -1) {
				s += norm + c;
				dfs(to[vt][c]);
				s.pop_back();
			}
		};
		if(vs != -1) dfs(vs);
		return ret;
	}
};
