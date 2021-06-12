// Aho-Corasick
//
// Link - points to the largest proper prefix in the trie
// End - number of inserted strings that end in this node of the trie
// Exit - links to the largest string that is suffix of the current one and was inserted
// (use exit to compute number of overlaping matches)
// get_link(at, c) leads to largest common prefix of string represented by trie[at] + c in the trie
//
// Complexity: 
// insert: O(|s| * log(sigma))
// build: O(n * log(sigma)), being n the sum of inserted string sizes
// get_link: O(|p|), being p the represented prefix, cheaper when amortized but be careful

struct AhoCorasick {
	vector<map<char, int>> trie;
	vector<int> link, end, exit;
	int id;

	AhoCorasick() : trie(1), end(1), id(1) {}

	void insert(const string& s) {
		int at = 0;
		for (char c : s) {
			auto it = trie[at].find(c);
			if (it == trie[at].end()) {
				at = trie[at][c] = id++;
				trie.emplace_back();
				end.push_back(0);
			}
			else at = it->second;
		}
		end[at]++;
	}
	int get_link(int at, char c) {
		while (at != -1 and not trie[at].count(c)) at = link[at];
		return at == -1 ? 0 : trie[at][c];
	}
	void build() {
		queue<int> q;
		q.push(0);
		link.resize(id), exit.resize(id);
		link[0] = exit[0] = -1;
		while (not q.empty()) {
			int i = q.front();
			q.pop();
			for (auto [c, j] : trie[i]) {
				link[j] = get_link(link[i], c);
				exit[j] = end[link[j]] ? link[j] : exit[link[j]];
				q.push(j);
			}
		}
	}
	void query(string t) { // query template
		int at = 0;
		for (char c : t) {
			at = get_link(at, c); 
			// at is in largest suffix of text that is present in the trie
		}
	}
};
