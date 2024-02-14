/**
 * Author: Wallace
 * Date: 14/02/2024
 * Description: n-1 iterations is sufficient to find all shortest paths
 * Time: O(V * E) -> O(N^2)
 * Status: Tested (https://cses.fi/problemset/result/8472591/)
 */

using T = array<ll, 3>;
vector<T> edges;
vector<ll> d(MAX, INF);
// INF = 0x3f3f3f3f3f3f3f3f, to avoid overflow

void BellmanFord(ll src, ll n) {
    d[src] = 0;
    for(ll i=0; i<n-1; i++) { // n-1 iterations
        for(auto [u, v, w] : edges) {
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
            }
        }
    }
}