// Binary search

// Time complexity O(log n);

int l=0, r=n-1;

while (l <= r) {
	int k = (l+r)/2;
	if (array[k] == x) return k
	if (array[k] > x) r = k-1;
	else l = k+1;
}
