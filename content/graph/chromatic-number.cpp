/** 
 * Author: YouKn0wWho and Wallace
 * Date: 29/07/2024
 * Description: Using bitmask DP and Inclusion-Exclusion principle, compute the Chromatic Number of a small graph.
 * Time: O(2^n n)
 */

ll ChromaticNumber(const vector<vector<ll>> &g) {
    ll n = g.size();
    ll N = 1 << n;
    ll ans = n;

    // adjacency list using bitmask
    vector<ll> adj(n);
    for (ll u = 0; u < n; u++)
        for (auto v : g[u])
            adj[u] |= (1 << v);
    
    // choose some primes to avoid hacking
    for (ll d : {7}) { //,11,21,33,87,93}) {
        ll mod = 1e9; mod += d;
        vector<ll> ind(N), aux(N, 1);
        ind[0] = 1;
        for (ll s = 1; s < N; s++) {
            ll u = __builtin_ctzll(s);
            ind[s] = ind[s ^ (1 << u)] + ind[(s ^ (1 << u)) & ~adj[u]];
        }
        for (ll k = 1; k < ans; k++) {
            ll w = 0;
            for (ll i = 0; i < N; ++i) {
                ll s = i ^ (i >> 1); // gray-code
                aux[s] = (aux[s] * ind[s]) % mod;
                w += (i & 1) ? aux[s] : -aux[s];
            }
            if (w % mod) ans = min(ans, k);
        }
    }
    return ans;
}