// Submasks
//
// Iterates in all submasks of mask (except for the empty submask, be careful)
// O(3^n)

for (int mask = 0; mask < (1 << n); mask++) {
	for (int smask = (mask-1)&mask; smask > 0; smask = (smask-1)&mask) {
		
	}
}
