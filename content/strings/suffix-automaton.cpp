/**
 * Author: Wallace, CP-algo, MagePetrus, AlbertoTDNeto
 * Date: 20/04/2024
 * Description: Suffix automaton, each node represents a set of end-pos equivalent substrings.
 * Solves A LOT of tasks!
 * Time: O(n) to create all nodes, O(n log{n}) to compute endpos size
 * Status: Tested in CSES
*/

// obs: O(alphabet) is considered constant
const ll alphabet = 27; // index #26 = char('{') (separator)

struct Automaton {
    struct State {
        ll link = 1, len = 0;
        array<ll, alphabet> down = {}; // 0 => non existent edge
        ll endpos = 0, fpos = -1;
 
        ll& operator [](const char &c) {
            return down[c-'a'];
        }
    };

    ll n = 2; // number of states
    vector<State> ton; // short for automaton :D
    string s;
    
    Automaton(string ss) : s(ss) {
        // root = 1, root.link = 0 (0 is a dummy node)
        ton.assign(2, {0});
        for(auto c : s) add(c);
        
        // build(); // remove if O(nlogn) is too much (s.size() ~ 2e6)
    }
 
    vector<pair<ll, ll>> order; // nodes ordered by len (decreasing)
    void build() { // compute endpos O(n log(n))
        for(ll i=1; i<n; i++) {
            order.pb({ton[i].len, i});
        }
        sort(order.rbegin(), order.rend());
        for(auto [len, i] : order) {
            ton[ ton[i].link ].endpos += ton[i].endpos;
        }
    }
    
    ll minlen(ll u) {
        return 1 + ton[ ton[u].link ].len;
    }

    ll last = 1;
    void add(char c) {
        ll u = n++;
        ll p = last;
        last = u;
 
        State node; // state[u]
        node.len = ton[p].len + 1;
        node.endpos = 1;
        node.fpos = node.len - 1;
        ton.pb(node);
 
        for (;p and !ton[p][c]; p = ton[p].link) 
            ton[p][c] = u;
 
        if (p == 0) return;
 
        ll q = ton[p][c];
        if (ton[p].len + 1 == ton[q].len) {
            ton[u].link = q;
            return;
        }
 
		ll clone = n++;
        State node2 = ton[q]; // state[clone]
        node2.endpos = 0;
        node2.len = ton[p].len + 1;
        ton.pb(node2);
 
		ton[u].link = ton[q].link = clone;
 
		for (; ton[p][c] == q; p = ton[p].link)
            ton[p][c] = clone;
	}

    // ----- //
    // Tasks //
    // ----- //

    // s1. Number of distinct substrings 
    // separated in a vector by their lengths
    // knowing that a state[u] cover all the substrings (suffixes) 
    // of size [minlen, len] represented by this state
    // Obs: for non-distinct substrings, the histogram is simply n, n-1, ... , 2, 1

    vector<ll> histogram() { // O(n)
        ll sz = s.size();
        vector<ll> ans(sz+1, 0);
 
        for(ll i=2; i<n; i++) {
            ll mnlen = minlen(i);
            ll len = ton[i].len;

            ans[mnlen] += 1;
            if (len + 1 <= sz)
                ans[len + 1] -= 1;
        }
 
        // delta encoding
        for(ll len=1; len<=sz; len++) {
            ans[len] += ans[len-1];
        }
        // ans[0] = 0, because the empty string is not considered as a substring
        return ans;
    }

    // s2. Find the lexicographically k-th substring (one can consider only the distincts or not)
    // The k-th substring corresponds to the lexicographically smallest one,
    // which is also the k-th path in the suffix automaton
    
    // Additionally, by creating the automaton on the duplicated string (S+S),
    // the k-th substring with k = s.size(), will give us the Smallest cyclic shift (Minimal Rotation)
    // For huge strings, remeber to not build() endpos which is O(n logn)

    // ps: number of substrings below node (including node)
    // ps[0] -> include repeated substring, ps[1] -> consider only distinct
    vector<ll> ps[2]; 

    void buildPS() { // O(n)
        assert(!order.empty()); // assert if build() was called

        ps[0].assign(n, 0), ps[1].assign(n, 0);

        for(ll k : {0, 1}) {
            for(auto [len, u] : order) {
                if (u != 1) {
                    ps[k][u] = (k ? 1 : ton[u].endpos);
                }

                for(auto v : ton[u].down) if (v) {
                    ps[k][u] += ps[k][v];
                }
            }
        }
    }

    string substring(ll k, bool distinct = true) { // O(V+E) = O(2sz+ 3sz) = O(5sz), sz = s.size()
        assert(!ps[0].empty()); // assert if buildPS() was called
 
        string ans = ""; // {k = 0} will return the empty string ""
 
        function<void (ll)> dfs = [&](ll u) {
            if (k <= 0) return;
            for(ll inc = 0; inc<alphabet; inc++) {
                char c = char('a' + inc);

                ll v = ton[u][c];
                if (!v) continue;

                ll sum = ps[distinct][v];

                if (k <= sum) {
                    ans += c;
                    k -= (distinct ? 1 : ton[v].endpos);
                    dfs(v);
                    if (k <= 0) return;
                }
                else k -= sum; // optimization
            }
        };
 
        dfs(1);
        return ans;
    }


    // -------- //
    // Patterns //
    // -------- //

    // p1. Check for occurrence of a pattern P
    // by returning the length of the longest prefix of P in S
    // A match occurs when len(prefix_pattern) == len(pattern)

    ll prefixPattern(string &p) { // O( p.size() )
        ll ans = 0, cur = 1;
        for(auto c : p) {
            if (ton[cur][c]) {
                cur = ton[cur][c];
                ans += 1;
            }
            else break;
        }
        return ans;
    }

    // p2. Count the numbers of occurrences of a pattern P

    ll countPattern(string &p) { // O( p.size() )
        assert(!order.empty()); // check if build() was called
        ll u = 1;
        for(auto c : p) {
            if (ton[u][c]) {
                u = ton[u][c];
            }
            else return 0; // no match
        }
        return ton[u].endpos;
    }

    // p3. Find the first position in which occurred the pattern (0-idx)

    ll firstPattern(string &p) { // O( p.size() )
        ll u = 1;
        for(auto c : p) {
            if (ton[u][c]) {
                u = ton[u][c];
            }
            else return -1; // no match
        }
        ll sz = p.size();
        return ton[u].fpos - sz + 1;
    }

    // p4. Longest Common Substring of P and S
    // In addition to returning the lcs, 
    // it returns an dp array with the lcs size for each end position i

    string lcs(string &p, vector<ll> &dp) { // O( p.size() )
        dp.assign(p.size(), 0);
        
        ll u = 1, match = 0, best = 0, pos = 0;

        for(ll i=0; i<(ll)p.size(); i++) {
            auto c = p[i];

            while(u > 1 and !ton[u][c]) { // no edge -> follow link
                u = ton[u].link;
                match = ton[u].len;
            }

            if (ton[u][c]) {
                u = ton[u][c];
                match++;
            }

            dp[i] = match;
            if (match > best) {
                best = match;
                pos = i;
            }
        }

        return p.substr(pos - best + 1, best);
    }
};