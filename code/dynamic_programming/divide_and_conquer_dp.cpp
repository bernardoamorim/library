// Divide and Conquer DP
//
// Optimize the cost of partitioning a array of size
// n in k subarrays (cost is dependent on the subarray extremes)
//
// Cost must obey, for all a < b < c < d:
// cost(a, d) - cost(b, c) >= cost(a, c) + cost(b, d)
// or if being A(i, k) the leftmost value that optimizes dp(i, k):
// A(i, k) <= A(i+1, k)
//
// cost can be done in MO's style
//
// Complexity: O(k.n.log(n))

int cost(int l, int r);

void dp(int k, int l, int r, int optl, int optr) {
	if (l > r) return;
 
	int m = (l + r) / 2, opt = -1;
 
	ll& p = memo[m][k&1] = LINF;
 
	for (int i = max(optl, m); i <= optr; i++) {
		ll cur = cost(m, i) + memo[i+1][~k&1];
		if (cur < p) p = cur, opt = i;
	}
	dp(k, l, m-1, optl, opt), dp(k, m+1, r, opt, optr);
}
 
ll dc_dp(int n, int k) {
	memo[n][0] = memo[n][1] = 0;
	for (int i = 0; i < n; i++) memo[i][0] = LINF;
	for (int i = 1; i <= k; i++) dp(i, 0, n-i, 0, n-i);
	return memo[0][k&1];
}
