// Chinese remainder theorem
//
// Combines modular linear equations x = a (mod m)
// Answer is kept in a
// The final m is the lcm of the m's and the answer is unique (mod lcm)
// The m's do not need to be coprimes
// If there's no solution, 'a' will be -1

ll egcd(ll a, ll b, ll& x, ll& y) {
	if (!a) {
		x = 0;
		y = 1;
		return b;
	}

	ll X, Y;
	ll g = egcd(b % a, a, X, Y);
	x = Y - (b / a) * X;
	y = X;

	return g;
}

struct crt {
	ll a, m;

	crt() : a(0), m(1) {}
	crt(ll a_, ll m_) : a(a_), m(m_) {}
	crt operator * (crt C) {
		ll x, y;
		ll g = egcd(m, C.m, x, y);
		if ((a - C.a) % g) a = -1;
		if (a == -1 or C.a == -1) return crt(-1, 0);
		ll lcm = m/g*C.m;
		ll ans = a + (x*(C.a-a)/g % (C.m/g))*m;
		return crt((ans % lcm + lcm) % lcm, lcm);
	}
};
