// LIS - Longest Increasing Subsequence
// 
// Returns the position of the elements of a LIS of v
//
// O(n.log(n))

template<typename T> vector<int> lis(vector<T>& v) {
    int n = v.size(), m = -1;
    vector<T> d(n+1, INF); // infinite value of the given type
    vector<int> l(n);
    d[0] = -INF;
    
    for (int i = 0; i < n; i++) {
        // For non-decreasing use upper_bound()
        int t = lower_bound(d.begin(), d.end(), v[i]) - d.begin();
        d[t] = v[i], l[i] = t, m = max(m, t);
    }
 
    int p = n;
    vector<T> ret;
    while (p--) {
    	if (l[p] == m) {
		ret.push_back(p);
        	m--;
        }
    }
    reverse(ret.begin(), ret.end());
    return ret;
}
