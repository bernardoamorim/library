// Fast exponenciation
//
// (x^y mod m) in O(log(y))

typedef long long ll;

ll fexp(ll x, ll y, ll m) { // iterative
	ll r = 1;
	while (y) {
		if (y & 1) r = (r*x) % m;
		y >>= 1;
		x = (x*x) % m;
	}
	return r;
}

ll fexp(ll x, ll y, ll m) { // recursive
	if (!y) return 1;
	ll ans = fexp(x*x % m, y/2, m);
	
	if(y % 2 == 0) return ans;
	else return x*ans % m;
}

// Matrix fast exponenciation 

// (x^y) (mod m) in O(log(y)*(x.size()))^3)

typedef vector<vector<ll>> mat;

mat id(int a) {
	mat ret(a, vector<ll>(a,0));
	for(int i=0; i<a; i++) for(int j=0; j<a; j++) ret[i][i] = 1;	

	return ret;
}

mat mmult(mat& x, mat& y, ll m) {
	int a = x.size(), b = y[0].size(), c = x[0].size();	

	mat z(a, vector<ll>(b,0));
	
	for(int i=0; i < a; i++)
		for(int j=0; j < b; j++)
			for(int k=0; k < c; k++)
				z[i][j] = (z[i][j]+x[i][k]*y[k][j]) % m;

	return z;
}

mat mfexp(mat &x, ll y, ll m) { // iterative
	mat z(x.size(),vector<ll>(x.size()));
	z = id(x.size());

	while(y) {
		if (y&1) z = mmult(z,x,m);
		y >>= 1;
		x = mmult(x,x,m);
	}

	return z;
}

mat mfexp(mat x, ll y, ll m) { // recursive
	
	if(!y) return id(x.size());

	mat z = mfexp(mmult(x,x,m), y/2, m);
	
	if(!(y%2)) return z;
	else return mmult(x,z,m);
}
