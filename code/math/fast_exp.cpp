// Fast exponenciation
//
// (x^y mod m) in O(log(y))

ll fexp(ll x, ll y, ll m) { // iterative
	ll r = 1;
	x %= m;
	while (y) {
		if (y & 1) r = (r*x) % m;
		y >>= 1;
		x = (x*x) % m;
	}
	return r;
}

ll fexp(ll x, ll y, ll m) { // recursive
	x %= m;
	if (!y) return 1;
	ll ans = fexp(x*x % m, y/2, m);
	
	if(y % 2 == 0) return ans;
	else return x*ans % m;
}
