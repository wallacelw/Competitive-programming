/**
 * Author: Wallace, Arpa
 * Date: 03/05/2024
 * Description: Using small to large technique, copy the big child to parent and iterate small children.
 * Time: O(n log{n})
*/

vector<vll> g(MAX), vec(MAX);
vector<ll> color(MAX), sz(MAX, 1), cnt(MAX, 0);

// get size of each subtree
void dfsSize(ll u, ll p = -1) {
    for(auto v : g[u]) if (v != p) {
        dfsSize(v, u);
        sz[u] += sz[v];
    }
}

// small to large dfs O(n log(n))
void dfs(ll u, ll p = -1, bool keep=true) {

    // find the biggest child 
    ll mx = 0, big = -1;
    for(auto v : g[u]) if (v != p) {
        if (sz[v] > mx) {
            mx = sz[v], big = v;
        }
    }

    // visit all small children 
    for(auto v : g[u]) if (v != p and v != big) {
        dfs(v, u, 0);
    }

    // visit big child, get his cnt
    if (big != -1) {
        dfs(big, u, 1);
        swap(vec[u], vec[big]);
    }

    // add itself
    vec[u].pb(u);
    cnt[color[u]] += 1;

    // add small children
    for(auto v : g[u]) if (v != p and v != big) {
        for(auto id : vec[v]) {
            vec[u].pb(id);
            cnt[color[id]] += 1;
        }
    }

    // remove cnt from small children
    if (keep == 0) {
        for(auto id : vec[u]) {
            cnt[ color[id] ] -= 1;
        }
    }
}