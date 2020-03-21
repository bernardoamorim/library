// Exponenciacao rapida
//
// (x^y mod m) em O(log(y))

typedef long long int ll;

ll pow(ll x, ll y, ll m) { // iterativo
	ll ret = 1;
	while (y) {
		if (y & 1) ret = (ret * x) % m;
		y >>= 1;
		x = (x * x) % m;
	}
	return ret;
}

ll pow(ll x, ll y, ll m) { // recursivo
	if (!y) return 1;
	ll ans = pow(x*x % m, y/2, m);
	
	if(y % 2 == 0) return ans;
	else return x*ans % m;
}
