/** 
 * Author: Wallace
 * Date: 28/09/2024
 * Description: Kosaraju to find if there are SCCs containing X and !X.
 * If not, find a valid assignment using the topological order
 * Time: O(V+E)
 */

// 0-idx graph !!!
struct TwoSat {
    ll N; // needs to be the twice of the number of variables
    // node[2x] => variable x
    // node[2x+1] => variable !x

    // g = graph; gi = transposed graph (all edges are inverted)
    vector<vll> g, gi; 
    ll idx = 1; // component idx
    vector<ll> comp, order; // order = topological order (reversed)
    vector<bool> vis, chosen;
    //  chosen[x] == 0 -> x was assigned 
    //  chosen[x] == 1 -> !x was assigned

    // n = number of variables (add +1 for 1-idx)
    TwoSat(ll n) : N(2*n), g(N), gi(N), comp(N, -1), vis(N), chosen(n, 0) {}

    void dfs(ll u) {
        vis[u] = 1;
        for (auto v : g[u]) if (!vis[v]) dfs(v); 
        order.pb(u);
    }

    void dfs2(ll u, ll c) {
        comp[u] = c;
        for (auto v : gi[u]) if (comp[v] == -1) dfs2(v, c); 
    }

    // returns true if there is a valid assignment
    bool solve() {
        for (ll i=0; i<N; i++) if (!vis[i]) dfs(i);

        for(ll i=ll(order.size()-1); i>=0; i--) {
            ll u = order[i];
            if (comp[u] == -1) dfs2(u, idx++);
        }

        for (ll i=0; i<N; i += 2) {
            // x and !x in the same component => contradiction
            if (comp[i] == comp[i+1]) return false; 
            chosen[i/2] = comp[i] < comp[i+1]; // choose latter node
        }
        
        return true;
    }

    // a (with flagA) implies => b (with flagB) 
    void add(ll a, bool fa, ll b, bool fb) {
        // {fa == 0} => a 
        // {fa == 1} => !a
        a = 2*a + fa;
        b = 2*b + fb;
        g[a].pb(b);
        gi[b].pb(a);
    }

    // force a variable to be a certain state (must be chosen)
    void force(ll a, bool fa) {
        add(a, fa^1, a, fa);
    }

    // xor operation: one must exist, and only one can exist
    void exclusive(ll a, bool fa, ll b, bool fb) {
        add(a, fa^0, b, fb^1);
        add(a, fa^1, b, fb^0);
        add(b, fb^0, a, fa^1);
        add(b, fb^1, a, fa^0);
    }

    // nand operation: no more than one can exist
    void nand(ll a, bool fa, ll b, bool fb) {
        add(a, fa^0, b, fb^1);
        add(b, fb^0, a, fa^1);
    }
};