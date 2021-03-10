// Gaussian Elimination in Z_2 (XOR)
// 
// D is the dimesion of the vector space
// add_vector(v) adds v to the vector space (maybe to its base)
// coordinates(v) returns v written in the coordinates of the current
// base of -1 if it does not belong to the vector space.
//
// Complexity:
// O(D.floor(D/32))

typedef bitset<D> bit;

bit base[D];
int rk = 0; // current rank of the vector space

void add_vector(bit v) {
	for(int i = 0; i < D; i++) if(v[i]) {
		if(base[i].none()) {
			base[i] = v, rk++;
			break;
		}
		v ^= base[i];
	}
}

bit coordinates(bit v) {
	bit coord = 0;
	for(int i = 0; i < D; i++) if(v[i]) {
		if(base[i].none()) return -1;
		v ^= base[i], coord.set(i);
	}
	return coord;
}
