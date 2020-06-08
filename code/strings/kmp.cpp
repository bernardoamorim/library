// KMP
//
// mathcing(s, t) returns the indices of the occurences of s in t
// autKMP buids KMP automaton
//
// Complexities:
// Time:
// pi - O(n)
// match - O(n + m)
// building automaton - O(|sigma|*n)
// n = |pattern| e m = |text|
//
// Original code: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/kmp.cpp

vector<int> pi(string s) {
	vector<int> p(s.size());
	for (int i = 1, j = 0; i < s.size(); i++) {
		while (j and s[j] != s[i]) j = p[j-1];
		if (s[j] == s[i]) j++;
		p[i] = j;
	}
	return p;
}

vector<int> matching(string& t, string& s) {
	vector<int> p = pi(s+'$'), match;
	for (int i = 0, j = 0; i < t.size(); i++) {
		while (j and s[j] != t[i]) j = p[j-1];
		if (s[j] == t[i]) j++;
		if (j == s.size()) match.push_back(i-j+1);
	}
	return match;
}

struct kmpaut : vector<vector<int>> {
	kmpaut(){}
	kmpaut (string& s) : vector<vector<int>>(26, vector<int>(s.size()+1)) {
		vector<int> p = pi(s);
		auto& aut = *this;
		aut[s[0]-'a'][0] = 1;
		for (char c = 0; c < 26; c++)
			for (int i = 1; i <= s.size(); i++)
				aut[c][i] = s[i]-'a' == c ? i+1 : aut[c][p[i-1]];
	}
};
