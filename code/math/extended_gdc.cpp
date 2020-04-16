// Euclides Extended GCD algorithm
//
// finds x and y so that ax + by = gcd(a,b) (the solution ins't unique)
//
// O(log(min(a, b)))

int egcd(int a, int b, int& x, int& y){
	if(!a){
		x = 0;
		y = 1;
		return b;
	}

	int X, Y;
	int gcd = egcd(b % a, a, X, Y);
	x = Y - (b / a) * X;
	y = X;

	return gcd;
}
