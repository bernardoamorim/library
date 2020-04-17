// Order Statistic Set

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
	
// declaration:
ord_set<int> s;

// things of set work normally:
for (auto i : s) cout << i << endl;
cout << s.size() << endl;

// k-th greater element O(log|s|):
// k=0: smallest element
cout << *s.find_by_order(k) << endl;

// how many are smaller than k O(log|s|):
cout << s.order_of_key(k) << endl;

// To make a multiset you have to
// use ord_set<pair<int,int> as a second
// parameters being something to diferenciate
// equal elements.
// s.order_of_key({k, -INF}) will return the 
// number of elements < k
