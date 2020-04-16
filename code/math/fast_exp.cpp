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

vector<vector<ll> > id(int sz) {
	vector<vector<ll> > Mid(sz, vector<ll>(sz));
	for(int i=0; i<sz; i++) {	
		for(int j=0; j<sz; j++) {
			if(i == j) Mid[i][j] = 1;
			else Mid[i][j] = 0;
		}
	}
	return Mid;
}

vector<vector<ll> > mprod(vector<vector<ll> > a, vector<vector<ll> > b, ll m) {
	int asz = (int) a.size();
	int bsz = (int) b[0].size();
	int csz = (int) a[0].size();	

	vector<vector<ll> > ret(asz, vector<ll>(bsz));
	
	for(int i=0; i < asz; i++) {
		for(int j=0; j < bsz; j++) {
			ll aux = 0;
			for(int k=0; k < csz; k++) {
				aux = (aux + a[i][k]*b[k][j]) % m;
			}	
			ret[i][j] = aux;
		}	
	}

	return ret;
}

vector<vector<ll> > mfexp(vector<vector<ll> > x, ll y, ll m) { // iterative
	int sz = (int) x.size();
	
	vector<vector<ll> > ret(sz,vector<ll>(sz));
	ret = id(sz);

	while (y) {
		if (y & 1) ret = mprod(ret,x,m);
		y >>= 1;
		x = mprod(x,x,m);
	}

	return ret;
}

vector<vector<ll> > mfexp(vector<vector<ll> > x, ll y, ll m) { // recursive
	
	if (!y) return id((int) x.size());

	vector<vector<ll> > ans = mfexp(mprod(x,x,m), y/2, m);
	
	if(y % 2 == 0) return ans;
	else return mprod(x,ans,m);
}
