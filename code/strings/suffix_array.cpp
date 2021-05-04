// Suffix-Array e LCP (Kasai's Algorithm)
//
// Complexity:
// suffix_array: O(n.log(n))
// lcp: O(n)

vector<int> suffix_array(string s) {
	s += '$';
	int n = s.size(), N = max(n, 260), ct = 0, k = 0;

	vector<int> p(n), sa(n);
	
	for(int i = 0; i < n; i++) sa[i] = i, p[i] = s[i];
	
	while (k < n) {
		vector<int> b(N), nsa(n), np(n);
		for (int i = 0; i < n; i++) 
			b[p[(i-k+n) % n]]++;
		for (int i = 1; i < N; i++) 
			b[i] += b[i-1];
		
		for (int i = n-1; i >= 0; i--) 
			nsa[--b[p[(sa[i]-k+n) % n]]] = (sa[i]-k+n) % n;
		
		sa = nsa, ct = 0;
		pair<int,int> prev, cur;
		for (int i = 0; i < n; i++) {
			cur = {p[sa[i]], p[(sa[i]+k) % n]};
			if (i and prev != cur) 
				ct++;
			np[sa[i]] = ct, prev = cur;
		}
		p = np, k = (k ? 2 * k : 1);
	}
	return vector<int>(sa.begin() + 1, sa.end());
}

vector<int> lcp(string s, vector<int> sa) {
	int n = s.size(), k = 0;
	vector<int> p(n), lcp(n);
	for (int i = 0; i < n; i++) 
		p[sa[i]] = i;
	for (int i = 0; i < n - 1; i++) {
		if (p[i]) {
			int j = sa[p[i]-1];
			while (s[i+k] == s[j+k]) 
				k++;
			lcp[p[i]] = k, k = max(k-1, 0);
		}
	}
	return vector<int>(lcp.begin()+1, lcp.end());
}
