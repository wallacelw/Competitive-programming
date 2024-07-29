/**
 * Author: Wallace
 * Date: 05/04/2024
 * Description: Simple DFS template with lambda syntax
 * Time: O(V + E)
*/

int32_t main(){ sws;
    // compute cardinality of each subtree
    vector<vll> g(n);
    vector<ll> card(n);
    vector<bool> vis(n); // redundant here

    function<ll (ll, ll)> dfs = [&](ll u, ll p) -> ll {
        if (vis[u]) return;
        vis[u] = 1;
        
        card[u] += 1;
        for(auto v : g[u]) if (v != p) {
            card[u] += dfs(v, u);
        }
        return card[u];
    };

    dfs(1, -1);
}  