// Inverso Modular
//
// Computa o inverso de a modulo b
// Se b eh primo, basta fazer
// a^(b-2)

long long inv(long long a, long long b){
	if(1 < a) return b - inv(b % a, a) * b/a;
	else return 1;
}
