/**
 * Author: Wallace
 * Date: 14/02/2024
 * Description: By using the property that n-1 iterations is sufficient to find all shortest paths
 * in a graph that doesn't have negative cycles. Iterate n times and retrieve the path using a vector of parents
 * Time: O(V * E) -> O(N^2)
 * Status: Tested (https://cses.fi/problemset/result/8472591/)
 */

using T = array<ll, 3>;
vector<T> edges;
vector<ll> d(MAX, INF), p(MAX, -1);
vector<ll> cycle;
// INF = 0x3f3f3f3f3f3f3f3f, to avoid overflow

void BellmanFordCycle(ll src, ll n) {
    d[src] = 0;
    ll x = -1; // possible node inside a negative cycle
    for(ll i=0; i<n; i++) { // n iterations
        x = -1;
        for(auto [u, v, w] : edges) {
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                p[v] = u;
                x = v;
            }
        }
    }

    if (x != -1) {
        // set x to a node, contained in a cycle in p[]
        for(ll i=0; i<n; i++) x = p[x]; 

        ll tmp = x;
        do {
            cycle.pb(tmp);
            tmp = p[tmp];
        } 
        while (tmp != x);
        cycle.pb(x);

        reverse(cycle.begin(), cycle.end());
    }
}