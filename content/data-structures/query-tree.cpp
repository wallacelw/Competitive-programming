/**
 * Author: Wallace, Usaco
 * Date: 28/04/2024
 * Description: All queries have an active intervals, build a tree to store these queries
 * and iterate it in dfs order with rollbacks. The code below solves the specific problem of Dynamic Conectivity.
 * Time: O(n log^2(n))
 * Status: Tested (https://cses.fi/problemset/result/9136292/)
*/

// include struct DSU {} (with rollback)

ll L=0, R;
struct QueryTree {
    struct Query {
        ll l, r; // this ranges is active in [l, r]
        ll u, v; // edge {u, v} will be merged in DSU
    };

    // each node is a vector of queries
    vector<vector<Query>> tree;

    QueryTree(ll n) {
        R = n;
        tree.assign(4*n + 10, {});
    }

    // l, r (tree); left, right (query)
    void add(Query q, ll l=L, ll r=R, ll i=1) {
        auto [left, right] = tie(q.l, q.r);
        
        if (right < l or r < left) return;
        
        if (left <= l and r <= right) {
            tree[i].pb(q);
            return;
        }

        ll mid = (l+r)/2;
        add(q, l, mid, 2*i);
        add(q, mid+1, r, 2*i+1);
    }

    void dfs(DSU &dsu, vector<ll> &ans, ll i = 1, ll l=L, ll r=R) {
        ll snap = dsu.snapshot();

        for(auto &q : tree[i]) {
            dsu.join(q.u, q.v);
        }

        if (l == r) { // leaf
            ans[l] = dsu.comps;
        }
        else {
            ll mid = (l + r)/2;
            dfs(dsu, ans, 2*i, l, mid);
            dfs(dsu, ans, 2*i + 1, mid+1, r);
        }

        // rollback
        dsu.rollback(snap);
    }
};

int32_t main(){ sws;
    ll n, m, k; cin >> n >> m >> k;

    QueryTree tree(k);
    map<pll, pll> queries;

    for(ll i=0; i<m; i++) { // time = 0
        ll u, v; cin >> u >> v;
        if (u > v) swap(u, v);
        queries[{u, v}] = {0, k};
    }

    for(ll t=1; t<=k; t++) {
        ll op, u, v; cin >> op >> u >> v;
        if (u > v) swap(u, v);
        if (op == 1) {
            queries[{u, v}] = {t, k};
        }
        else {
            queries[{u, v}].ss = t-1;
            QueryTree::Query q;
            tie(q.l, q.r) = queries[{u, v}];
            tie(q.u, q.v) = {u, v};
            tree.add(q);
            queries.erase({u, v});
        }
    }

    for(auto [key, range] : queries) {
        QueryTree::Query q;
        tie(q.l, q.r) = range; 
        tie(q.u, q.v) = key;
        tree.add(q);
    }
    
    vector<ll> ans(k+1);
    DSU dsu(n);
    tree.dfs(dsu, ans);

    for(auto val : ans)
        cout << val << " ";
    cout << endl;
}