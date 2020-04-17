// Fast exponenciation
//
// (x^y mod m) in O(log(y))

typedef long long ll;

ll fexp(ll x, ll y, ll m) { // iterative
	ll ret = 1;
	while (y) {
		if (y & 1) ret = (ret * x) % m;
		y >>= 1;
		x = (x * x) % m;
	}
	return ret;
}

ll fexp(ll x, ll y, ll m) { // recursive
	if (!y) return 1;
	ll ans = fexp(x*x % m, y/2, m);
	
	if(y % 2 == 0) return ans;
	else return x*ans % m;
}

// Matrix fast exponenciation 

// (x^y) (mod m) in O(log(y)*(M.sz())^3)

typedef vector<vector<ll> > mat;

mat idty(int a) {
	mat id(a, vector<ll>(a,0));
	for(int i=0; i < a; i++) {	
		for(int j=0; j < a; j++) 
			if(i == j) id[i][j] = 1;
	}
	return id;
}

mat mmul(mat x, mat y, ll m) {
	int a = (int) x.size();
	int b = (int) y[0].size();
	int c = (int) x[0].size();	

	mat z(a, vector<ll>(b,0));
	
	for(int i=0; i < a; i++) {
		for(int j=0; j < b; j++) {
			for(int k=0; k < c; k++) {
				z[i][j] += x[i][k]*y[k][j];
				z[i][j] %= m;	
			}	
		}	
	}

	return z;
}

mat mfexp(mat x, ll y, ll m) { // iterative
	int sz = (int) x.size();
	
	mat z(sz,vector<ll>(sz));
	z = idty(sz);

	while (y) {
		if (y & 1) z = mmul(z,x,m);
		y >>= 1;
		x = mmul(x,x,m);
	}

	return z;
}

mat mfexp(mat x, ll y, ll m) { // recursive
	
	if (!y) return id((int) x.size());

	mat z = mfexp(mmul(x,x,m), y/2, m);
	
	if(y % 2 == 0) return z;
	else return mmul(x,z,m);
}
