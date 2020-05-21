// String Hashing
//
// To avoid colisions:
// -Use more than one MOD
// -Only conpare strings of the same size
//
// ex: str_hash<int(1e9+7)> h(str);
//	   ll val = h(10,20);
//
// Complexities:
// Time : 
// constructor - O(|str|)
// operator() - O(1)
//
// Space - O(|str|)

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

int uniform(int l, int r){
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}


template<int MOD> struct str_hash {
	static int a;
	int n;
	string s;
	vector<ll> h, power;
	str_hash(string s_) : n(sz(s_)), s(s_), h(n), power(n) {
		power[0] = 1;
		for(int i=1; i<n; i++) power[i] = power[i-1]*a % MOD;
		// higher powers on the left-hand side so we don't need to use mod_inv
		h[0] = s[0]; 
		for(int i=1; i<n; i++) h[i] = (h[i-1]*a + s[i]) % MOD;
	}
	ll operator()(int i, int j) {
		if(!i) return h[j];
		return ((h[j] - h[i-1]*power[j-i+1]) % MOD + MOD) % MOD;
	}
};

// first parameter must be greater than the size of the alphabet
template<int MOD> int str_hash<MOD>::a = uniform(50, MOD-1);
