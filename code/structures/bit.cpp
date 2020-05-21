// BIT
//
// BIT of sum 1-based, v 0-based
// To change the value in p to x do:
// 	update(x - query(p, p), p)
// l_bound(x) returns the smallest p such that
// query(1, p+1) > x    (0 based!)
//
// Complexities:
// 
// Time: 
// build - O(n)
// update - O(log(n))
// query - O(log(n))
// l_bound - O(log(n))
// 
// Space: O(n)
//
// Original: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/BIT.cpp
//
// Verification: https://codeforces.com/contest/1354/problem/D

int n;
int bit[MAX];
int v[MAX];

void build() {
	bit[0] = 0;
	for (int i = 1; i <= n; i++) bit[i] = v[i - 1];

	for (int i = 1; i <= n; i++) {
		int j = i + (i & -i);
		if (j <= n) bit[j] += bit[i];
	}
}

// soma x na posicao p
void poe(int x, int p) {
	for (; p <= n; p += p & -p) bit[p] += x;
}

// soma [1, p]
int pref(int p) {
	int ret = 0;
	for (; p; p -= p & -p) ret += bit[p];
	return ret;
}

// soma [a, b]
int query(int a, int b) {
	return pref(b) - pref(a - 1);
}

int l_bound(ll x) {
	int p = 0;
	for (int i = MAX2; i+1; i--) if (p + (1<<i) <= n
		and bit[p + (1<<i)] <= x) x -= bit[p += (1<<i)];
	return p;
}
