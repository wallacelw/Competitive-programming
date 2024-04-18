/**
 * Author: CP-algo, Wallace
 * Date: 17/04/2024
 * Description: Suffix automaton, each node represents a set of end-pos equivalent substrings.
 * Solves A LOT of tasks!
 * Time: O(n log{k}), n = s.size(), k = characters used
 * Status: Tested in CSES
*/

struct Automaton {
    struct State {
        ll len = 0, link = 1;
        map<char, ll> down = {}; // 0 => non existent edge
        ll cnt = 0, fpos = -1;

        ll& operator [](const char c) {
            return down[c];
        }
    };
 
    ll n = 2; // number of states
    vector<State> ton; // short for automaton :D
    vector<ll> order_len;
    string s;
    
    Automaton(string ss) : s(ss) {
        // root = 1, root.link = 0 (0 is a dummy node)
        ton.assign(2, {0, 0});

        for(auto c : s) add(c);

        for(ll i=1; i<n; i++) order_len.pb(i);
        sort(order_len.begin(), order_len.end(), [&](auto l, auto r) {
            return ton[l].len > ton[r].len;
        });
        for(auto i : order_len) {
            ll j = ton[i].link;
            if (j != 1) ton[j].cnt += ton[i].cnt;
        }
    }

    ll last = 1;
    void add(char c) {
        ll cur = n++;
        ll p = last;
        last = cur;

        State node; // state[cur]
        node.len = ton[p].len + 1;
        node.cnt = 1;
        node.fpos = node.len - 1;
        ton.pb(node);

        for (;p and !ton[p].down.count(c); p = ton[p].link) 
            ton[p][c] = cur;

        if (p == 0) return;

        ll q = ton[p][c];
        if (ton[p].len + 1 == ton[q].len) {
            ton[cur].link = q;
            return;
        }

		ll clone = n++;
        State node2 = ton[q]; // state[clone]
        node2.cnt = 0;
        node2.len = ton[p].len + 1;
        ton.pb(node2);

		ton[cur].link = ton[q].link = clone;

		for (; ton[p][c] == q; p = ton[p].link)
            ton[p][c] = clone;
	}

    // ----- //
    // Tasks //
    // ----- //

    // s1. Number of distinct substrings
    // separated in a vector by their lengths
    // using the property that: minlen(cur) = 1 + len(link(cur))
    // and that state[cur] cover all the substrings (suffixes) 
    // of size [minlen, len] represented by this state

    vector<ll> distinctSubstrings() { // O(n)
        ll sz = s.size();
        vector<ll> ans(sz+1, 0);
 
        for(ll i=2; i<n; i++) {
            ll j = ton[i].link;
            ll minlen = 1 + ton[j].len;
            ll len = ton[i].len;
 
            ans[minlen] += 1;
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
    // This may have a big complexity nevertheless, need to optimize

    // number of substrings below node (including node)
    // ps[0] -> include repeated substring, ps[1] -> consider only distinct
    vector<ll> ps[2]; 

    void buildPS() {
        ps[0].assign(n, 0), ps[1].assign(n, 0);

        for(ll k : {0, 1}) {
            for(auto i : order_len) {
                if (i != 1) 
                    ps[k][i] = (k ? 1 : ton[i].cnt);

                for(auto [c, j] : ton[i].down) {
                    ps[k][i] += ps[k][j];
                }
            }
        }
    }

    string substring(ll k, bool distinct = true) { // O(V+E) = O(2sz+ 3sz) = O(5sz), sz = s.size()
        assert(!ps[0].empty());
 
        string ans = ""; // {k = 0} will return the empty string ""
 
        function<void (ll)> dfs = [&](ll u) {
            if (k <= 0) return;
            for(auto [c, v] : ton[u].down) {
                ll sum = ps[distinct][v];
                if (k <= sum) {
                    ans += c;
                    k -= (distinct ? 1 : ton[v].cnt);
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
            if (ton[cur].down.count(c)) {
                cur = ton[cur][c];
                ans += 1;
            }
            else break;
        }
        return ans;
    }

    // p2. Count the numbers of occurrences of a pattern P

    ll countPattern(string &p) { // O( p.size() )
        ll u = 1;
        for(auto c : p) {
            if (ton[u].down.count(c)) {
                u = ton[u].down[c];
            }
            else return 0; // no match
        }
        return ton[u].cnt;
    }

    // p3. Find the first position in which occurred the pattern (0-idx)

    ll firstPattern(string &p) { // O( p.size() )
        ll u = 1;
        for(auto c : p) {
            if (ton[u].down.count(c)) {
                u = ton[u].down[c];
            }
            else return -1; // no match
        }
        ll sz = p.size();
        return ton[u].fpos - sz + 1;
    }
};