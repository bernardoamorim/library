// Sieve of Eratosthenes

// Sieve
//
// Sieve[i] == true if i is prime
//
// build_sieve - O(n log(log(n)))

vector<bool> sieve(MAX,true);

void build_sieve(int lim) {
	sieve[0] = sieve[1] = false;
	for(ll i=4; i < lim; i += 2) sieve[i] = false;
	for(ll i=3; i < lim; i += 2) if(sieve[i] == true)
		for(ll j = i*i; j < lim; j += i) sieve[j] = false;
}

// Sieve of Divisors
//
// Finds the largest prime divisor of a number in [1, lim)
// A number is prime iff sieve[x] == x
//
// build_sieve - O(n log(log(n)))
// fact - O(log(n))

int sieve[MAX];

void build_sieve(int lim) {
	fill(sieve, sieve + lim, 1);

	for(int i=2; i < lim; i += 2) sieve[i] = 2;
	for(int i=3; i < lim; i += 2) if(sieve[i] == 1)
		for(int j = i; j < lim; j += i) sieve[j] = i;
}

void fact(vector<int>& v, int n) {
	if (n != sieve[n]) fact(v, n/sieve[n]);
	v.push_back(sieve[n]);
}
