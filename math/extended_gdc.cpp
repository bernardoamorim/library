// Euclides Extended GCD algorithm
//
// Finds and return x and y so that ax + by = gcd(a,b) (the solution ins't unique)
// Returns {gcd(a,b), x, y}
//
// O(log(min(a, b)))

tuple<ll, ll, ll> ext_gcd(ll a, ll b) {
    if (a == 0) return {b, 0, 1};
 
    auto [gcd, x, y] = ext_gcd(b % a, a);
 
    return {gcd, y - (b/a) * x, x};
}
