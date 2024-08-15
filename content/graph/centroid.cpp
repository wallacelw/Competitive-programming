/** 
 * Author: MvKaio, Wallace
 * Date: 14/08/2024
 * Description: find the centroid(s) of a tree
 * Time: O(V)
 * Status: Tested (https://cses.fi/problemset/result/10194443/)
 */

// 0-idx
struct Centroid {
    vector<vector<ll>> g;
    ll n;
    vector<ll> sz, cs; // cs has the vertices that are centroids

    void find_centroid(ll u, ll p = -1) {
        sz[u] = 1;
        bool cent = true;
        for(auto v : g[u]) if (v != p) {
            find_centroid(v, u), sz[u] += sz[v];
            if (sz[v] > n/2) cent = false;
        }
        if (cent and n - sz[u] <= n/2) cs.pb(u);
    }

    // initialize G with the correct size, so that n = vertices (exactly) !!
    Centroid(vector<vector<ll>> &g_) : g(g_), n(g.size()), sz(n) {
        find_centroid(0);
    }
};