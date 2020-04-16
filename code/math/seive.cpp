// Eratosthenes Seive variations

// Finds the greatest prime divisor
// A number is prime iff div[x] == x
// fact factorates a number <= lim
// The factoration is ordered
//
// seive - O(n log(log(n)))
// fact - O(log(n))

int divi[MAX];

void seive(int lim) {
	for (int i = 1; i <= lim; i++) divi[i] = 1;

	for (int i = 2; i <= lim; i++) if (divi[i] == 1)
		for (int j = i; j <= lim; j += i) divi[j] = i;
}

void fact(vector<int>& v, int n) {
	if (n != divi[n]) fact(v, n/divi[n]);
	v.push_back(divi[n]);
}

// Sieve of divisors
//
// Finds the number of divisors
// or its summation
//
// O(n log(n))

int divi[MAX];

void crivo(int lim) {
	for (int i = 1; i <= lim; i++) divi[i] = 1;

	for (int i = 2; i <= lim; i++)
		for (int j = i; j <= lim; j += i) {
			// for number of divisors
			divi[j]++;
			// for summation of divisors
			divi[j] += i;
		}
}

// Totient Sieve
//
// Finds the value of the 
// Euler's totient function
//
// O(n log(log(n)))

int tot[MAX];

void crivo(int lim) {
	for (int i = 1; i <= lim; i++) tot[i] = i;

	for (int i = 2; i <= lim; i++) if (tot[i] == i)
		for (int j = i; j <= lim; j += i)
			tot[j] -= tot[j] / i;
}
