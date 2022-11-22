## SAT (Boolean satisfiability problem)

SAT is NP-Complete

### 2-SAT (2-satisfiability)

2-SAT is a restriction of the SAT problem, in 2-SAT every clause has exactly two literals.

Can be solved with graphs in *O(Vertices + Edges)*.

```cpp
// 0-idx graph !!!!
struct TwoSat {
    ll N; // needs to be the twice of the number of variables
    // node with idx 2x => variable x
    // node with idx 2x+1 => negation of variable x

    vector<vll> g, gt; 
    // g = graph; gt = transposed graph (all edges are inverted)

    TwoSat(ll n) { // number of variables
        N = 2*n;
        g.assign(N, vll());
        gt.assign(N, vll());
    }

    vector<bool> used;
    vll order, comp;
    vector<bool> assignment;
    //  assignment[x] == 1 -> x was assigned 
    //  assignment[x] == 0 -> !x was assigned 

    // dfs1 and dfs2 are part of kosaraju algorithm
    void dfs1(ll u) {
        used[u] = true;
        for (ll v : g[u]) if (!used[v]) dfs1(v); 
        order.pb(u); // topological order
    }

    void dfs2(ll u, ll timer) {
        comp[u] = timer;
        for (ll v : gt[u]) if (comp[v] == -1) dfs2(v, timer); 
    }

    bool solve_2SAT() {
        order.clear();
        used.assign(N, false);
        for (ll i = 0; i < N; i++) if (!used[i]) dfs1(i);

        comp.assign(N, -1);
        for (ll i = 0, j = 0; i < N; i++) {
            ll u = order[N - i - 1]; // reverse order
            if (comp[u] == -1) dfs2(u, j++);
        }

        assignment.assign(N/2, false);
        for (ll i = 0; i < N; i += 2) {
            if (comp[i] == comp[i + 1]) return false; // x and !x contradiction
            assignment[i / 2] = comp[i] > comp[i + 1];
        }
        return true;
    }

    void add_disjunction(ll a, bool na, ll b, bool nb) {
        // disjunction of (a, b) => if one of the two variables is false, then the other one must be true
        // na and nb signify whether a and b are to be negated 
        // na == 1 => !a ; na == 0 => a
        // nb == 1 => !b ; nb == 0 => b
        a = 2*a ^ na;
        b = 2*b ^ nb;
        ll neg_a = a ^ 1;
        ll neg_b = b ^ 1;
        g[neg_a].pb(b);
        g[neg_b].pb(a);
        gt[b].pb(neg_a);
        gt[a].pb(neg_b);
    }
};
```

#### Example of Application:

https://cses.fi/problemset/task/1684/ (Giant Pizza)

```cpp
int32_t main(){ sws;
    ll m, n; cin >> m >> n;
 
    TwoSat twoSat(n);
 
    for(ll i=0; i<m; i++) {
        char charA, charB;
        ll a, b;
        cin >> charA >> a >> charB >> b;
        // at least one => (!a 'disjoint' !b)
        bool na = (charA == '-');
        bool nb = (charB == '-');
        twoSat.add_disjunction(a-1, na, b-1, nb);
    }
 
    if (!twoSat.solve_2SAT()) cout << "IMPOSSIBLE" << endl;
    else {
        for(ll i=0; i<n; i++) {
            if (twoSat.assignment[i]) cout << "+ ";
            else cout << "- ";
        }
        cout << endl;
    }
}   
```

### Extended Version

Possibly faster implementation, with redundant functions to facilitate logic.

```cpp
struct TwoSat { // copied from kth-competitive-programming/kactl
	ll N;
	vector<vll> gr;
	vll values; // 0 = false, 1 = true
	TwoSat(ll n = 0) : N(n), gr(2*n) {} // crazy constructor, n = number of variables
	ll addVar() { // (optional)
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}
	void either(ll f, ll j) {
		f = max(2*f, -1-2*f);
		j = max(2*j, -1-2*j);
		gr[f].push_back(j^1);
		gr[j].push_back(f^1);
	}
	void atMostOne(const vll& li) { // (optional)
		if ((ll)li.size() <= 1) return;
		ll cur = ~li[0];
		for(ll i=2; i<(ll)li.size(); i++) {
			ll next = addVar();
			either(cur, ~li[i]);
			either(cur, next);
			either(~li[i], next);
			cur = ~next;
		}
		either(cur, ~li[1]);
	}
	vll _val, comp, z; ll time = 0;
	ll dfs(ll i) {
		ll low = _val[i] = ++time, x; z.push_back(i);
		for(ll e : gr[i]) if (!comp[e])
			low = min(low, _val[e] ?: dfs(e));
		if (low == _val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = low;
			if (values[x>>1] == -1)
				values[x>>1] = x&1;
		} while (x != i);
		return _val[i] = low;
	}
	bool solve() {
		values.assign(N, -1);
		_val.assign(2*N, 0); comp = _val;
		for(ll i=0; i<2*N; i++) if (!comp[i]) dfs(i);
		for(ll i=0; i<N; i++) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};
```