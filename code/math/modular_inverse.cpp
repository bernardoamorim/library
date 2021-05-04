// Modular Inverse
//
// Compute inverse of a mod b
// only guaranteed to exist if a and b are coprimes
// If b is prime inv(a, b) = a^(b-2)
//
// O(log(m))

ll inv(ll a, ll b) {
	return a > 1 ? b - inv(b % a, a) * b / a : 1;
}
