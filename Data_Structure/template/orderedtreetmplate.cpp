#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds ;
using namespace std ;
typedef tree <int , null_type , less <int>, rb_tree_tag ,
tree_order_statistics_node_update> ordered_set ;

ordered_set myset;

int main() {
	myset.insert(1);
	myset.insert(4);
	myset.insert(5);
	// find the kth largest key 0-indexed
	cout << *myset.find_by_order(0) << endl;
	// order of the key, 0-index
	cout << myset.order_of_key(4) << endl;
	cout << *myset.find_by_order(1) << endl;
	cout << myset.order_of_key(6) << endl;
	// set size
	cout << myset.size() << endl;
	// find
	cout << (myset.find(4) != myset.end()) << endl;
	// remove
	myset.erase(4);
	tree <int , null_type , less <int>, rb_tree_tag ,
tree_order_statistics_node_update> :: iterator iter = myset.begin();
	while (iter != myset.end()) {
		cout << *iter << endl;
		iter++;
	}
	return 0;
}
