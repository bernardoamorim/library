// Modular inverse
//
// Computes the inverse of a modulo b
// If b is prime, you can simply do:
// a^(b-2)

ll inv(ll a, ll b){
	if(1 < a) return b - inv(b % a, a) * b/a;
	else return 1;
}
