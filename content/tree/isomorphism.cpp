/** 
 * Author: MvKaio, Wallace
 * Date: 14/08/2024
 * Description: compute the hash value of a tree (root and unrooted)
 * Time: O(V \log{V})
 * Status: Tested (https://cses.fi/problemset/result/10194413/)
 */

map<vector<int>, int> hashmap;

// 0-idx implementation
struct Tree {
    vector<vector<int>> g;
    int n;
    vector<int> sz, cs;

    // initialize G with the correct size, so that n = vertices (exactly) !!
    Tree(vector<vector<int>> &g_) : g(g_), n(g.size()), sz(n) { }

    // function to get the centroid(s) of a tree and appends to a vector
    void find_centroid(int u, int p = -1) {
        sz[u] = 1;
        bool cent = true;
        for(auto v : g[u]) if (v != p) {
            find_centroid(v, u), sz[u] += sz[v];
            if (sz[v] > n/2) cent = false;
        }
        if (cent and n - sz[u] <= n/2) cs.pb(u);
    }

    // get the hash of a rooted tree in (root = u) (returned hash is int)
    int hash(int u, int p = -1) {
        vector<int> h;
        for(int v : g[u]) if (v != p) h.pb(hash(v, u));
        sort(h.begin(), h.end());
        if (!hashmap.count(h)) hashmap[h] = hashmap.size();
        return hashmap[h];
    }

    // get the hash of an unrooted tree (returned hash is long long)
    ll uhash() {
        find_centroid(0); // 0-idx
        if (cs.size() == 1) return hash(cs[0]);
        ll h1 = hash(cs[0], cs[1]), h2 = hash(cs[1], cs[0]);
        return (min(h1, h2) << 30) + max(h1, h2);
    }
};