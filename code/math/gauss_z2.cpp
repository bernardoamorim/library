// Gaussian Elimination in Z_2 (XOR)
// 
// D is the dimesion of the vector space
//
// add_vector(v): adds v to the base B
// coordinates(v): returns v written in the coordinates of B if v \in [B] and -1 if v \notin [B]
//
// Complexity: O(D.floor(D/32))

template<int D> struct gauss_z2 {
	bitset<D> basis[D]; // vectors of the basis (the vector in position i has i as the first lit bit)
	int rk = 0; // rank of the current basis

	void add_vector(bitset<D> v) {
		for(int i = D-1; i >= 0; i--) if(v[i]) {
			if(not basis[i][i]) {
				basis[i] = v, rk++;
				return;
			}
			v ^= basis[i];
		}
	}
	bitset<D> coordinates(bitset<D> v) {
		bitset<D> coord = 0;
		for(int i = D-1; i >= 0; i--) if(v[i]) {
			if(not basis[i][i]) return -1;
			v ^= basis[i], coord.set(i);
		}
		return coord;
	}
};
