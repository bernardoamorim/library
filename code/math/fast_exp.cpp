// Fast exponenciation
//
// (x^y mod m) in O(log(y))

ll fexp(ll x, ll y, ll m) { // iterative
	ll r = 1;
	x %= m;
	while(y > 0) {
		if(y & 1) r = (r*x) % m;
		y >>= 1;
		x = (x*x) % m;
	}
	return r;
}
