// Euler Totient Function
//
// Finds |{m \in N, m <= n ^ gdc(n,m) = 1}|
//
// O(sqrt(n))

int tot(int n){
	int ret = n;

	for (int i = 2; i*i <= n; i++) {
		if (n % i == 0) {
			while (n % i == 0) n /= i;
			ret -= ret / i;
		}
	}
	if (n > 1) ret -= ret / n;

	return ret;
}
