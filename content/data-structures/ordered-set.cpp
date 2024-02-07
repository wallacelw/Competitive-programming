/**
 * Author: Wallace
 * Date: 07/02/2024
 * Description: Set with index operators, implemented by gnu pbds
 * Remember to compile with gcc!!
 * Time: O(log(N)) but with slow constant
 */

// 0-idx
// find_by_order(i) -> iterator to elem with index i; O(log(N))
// order_of_key(i) -> index of key; O(log(N))

// Ordered Set
#include <bits/extc++.h>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Ordered Map
#include <bits/extc++.h>
using namespace __gnu_pbds;
template <class K, class V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;