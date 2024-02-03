## 2-SAT (2-satisfiability)

SAT (Boolean satisfiability problem) is NP-Complete.

2-SAT is a restriction of the SAT problem, in 2-SAT every clause has exactly two literals.

Can be solved with graphs in *O(Vertices + Edges)*.

The algorithm uses kosaraju to check if any (X and !X) are in the same Strongly Connected Component (which implies that the problem is impossible). If not, there is at least one solution, which can be generated using the topological sort of the same kosaraju (opting for the variables that appers latter in the sorted order)

```cpp
// 0-idx graph !!!!
struct TwoSat {
    ll N; // needs to be the twice of the number of variables
    // node with idx 2x => variable x
    // node with idx 2x+1 => variable !x

    vector<vll> g, gi; 
    // g = graph; gi = transposed graph (all edges are inverted)

    TwoSat(ll n) { // number of variables (add +1 for 1-idx)
        N = 2*n;
        g.assign(N, vll());
        gi.assign(N, vll());
    }

    ll idx; // component idx
    vector<ll> comp, order; // topological order (reversed)
    vector<bool> vis, chosen;
    //  chosen[x] == 0 -> x was assigned 
    //  chosen[x] == 1 -> !x was assigned 

    // dfs and dfs2 are part of kosaraju algorithm
    void dfs(ll u) {
        vis[u] = 1;
        for (ll v : g[u]) if (!vis[v]) dfs(v); 
        order.pb(u);
    }

    void dfs2(ll u, ll c) {
        comp[u] = c;
        for (ll v : gi[u]) if (comp[v] == -1) dfs2(v, c); 
    }

    bool solve() {
        vis.assign(N, 0);
        order = vector<ll>();
        for (ll i = 0; i < N; i++) if (!vis[i]) dfs(i);

        comp.assign(N, -1); // comp = 0 can exist
        idx = 1;
        for(ll i=(ll)order.size()-1; i>=0; i--) {
            ll u = order[i];
            if (comp[u] == -1) dfs2(u, idx++);
        }

        chosen.assign(N/2, 0);
        for (ll i = 0; i < N; i += 2) {
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

    // force a state for a certain variable (must be true)
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
```