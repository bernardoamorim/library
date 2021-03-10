// Gaussian Elimination in Z_2 (XOR)
// 
// const int D is the dimesion of the vector space
//
// add_vector(v): adds v to the base B
// coordinates(v): returns v written in the coordinates of B if v \in [B] and -1 if v \notin [B].
//
// Complexity: O(D.floor(D/32))

typedef bitset<D> bit;

bit base[D];
int rk = 0; // current rank [B]

void add_vector(bit v) {
	for(int i = 0; i < D; i++) if(v[i]) {
		if(base[i].none()) {
			base[i] = v, rk++;
			return;
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
