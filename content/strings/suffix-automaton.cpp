/**
 * Author: CP-algo, Wallace
 * Date: 17/04/2024
 * Description: Suffix automaton, each node represents a set of end-pos equivalent substrings.
 * Solves A LOT of tasks!
 * Time: O(n log{k}), n = s.size(), k = characters used
 * Status: Tested in CSES
*/

struct SuffixAutomaton {
    struct State {
        ll len = 0, link = 0; // link = the state id connected by the uplink
        map<char, ll> down = {}; // ids of connected states below
 
        // extra for problems {p2, p3}
        bool isClone = false;
        ll first_pos = -1;
        //
    };
 
    ll n = 1; // number of states
    vector<State> ton; // short for automaton :D
    string s;
 
    SuffixAutomaton(string ss) : s(ss) {
        ton.pb( {0, -1} ); // root = 0
        for(auto c : s) add(c);
    }
 
    ll last = 0; // last state's id
    void add(char c) {
        ton.pb( {ton[last].len+1} );
        ll cur = n++;
        
        // extra for problems {p3}
        ton[cur].first_pos = ton[cur].len - 1;
        //
 
        ll p = last;
        while (p != -1 and !ton[p].down.count(c)) {
            ton[p].down[c] = cur;
            p = ton[p].link;
        }
 
        if (p != -1) {
            ll q = ton[p].down[c];
            if (ton[p].len + 1 == ton[q].len) {
                ton[cur].link = q;
            } 
            else {
                ton.pb(ton[q]);
                ll clone = n++;
                ton[clone].len = ton[p].len + 1;
 
                // extra for problems {p2}
                ton[clone].isClone = true;
                //
 
                while (p != -1 and ton[p].down[c] == q) {
                    ton[p].down[c] = clone;
                    p = ton[p].link;
                }
                ton[cur].link = ton[q].link = clone;
            }
        }
        last = cur;
    }
 
//// problems that can be solved ////
// OBS: an additional time complexity of log{k} will be used when implementing with map
 
    // s1. Number of distinct substrings
    // separated in a vector by their lengths
    // using the property that: minlen(cur) = 1 + len(link(cur))
    // and that state[cur] cover all the substrings 
    // (suffixes) of size [minlen, len] represented by this state
    vector<ll> distinctSubstrings() { // O(n)
        ll sz = s.size();
        vector<ll> ans(sz+1, 0);
 
        for(ll i=1; i<n; i++) {
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
 
    // s2. find the lexicographically k-th substring
    // The k-th substring corresponds to the lexicographically  
    // k-th path in the suffix automaton
 
    // Additionally, by creating the automaton on the duplicated string (S+S),
    // the k-th substring with k = s.size(), will give us the Smallest cyclic shift (Minimal Rotation)
    string substring(ll k) { // O(V+E) = O(2sz+ 3sz) = O(5sz), sz = s.size()
        string ans = ""; // {k = 0} will return the empty string ""
        ll idx = 0;

        // iterative dfs to avoid stack overflow
        vector<bool> vis(n, 0);
        stack<pair<ll, char>, vector<pair<ll, char>>> st;
        st.push({0, 0}); // root
        
        while(st.size()) {
            auto [u, concat] = st.top();

            if (vis[u]) { // pop command 
                ans.pop_back();
                st.pop();
                continue;
            }
            vis[u] = true;
            
            if (concat != 0) {
                ans += concat; idx++;
                if (idx == k) break;
            } 

            auto edges = ton[u].down;
            for(auto itr = edges.rbegin(); itr != edges.rend(); itr++) {
                auto [c, v] = *itr;
                st.push({v, c});
            }
        }

        return ans;
    }
 
 
/// Involving Patterns ///
 
    // p1. Check for occurrence of a pattern P
    // by returning the length of the longest prefix of P in S
    ll checkPattern(string &p) { // O( p.size() )
        ll ans = 0;
        ll cur = 0;
        for(auto c : p) {
            if (ton[cur].down.count(c)) {
                cur = ton[cur].down[c];
                ans += 1;
            }
            else break;
        }
        return ans;
    }
 
    // p2. Count the numbers of occurrences of a pattern P
    vector<ll> cnt;
    void count() { // O(n log(n))
        cnt.assign(n, 0);
        vector<pll> order;
        for(ll i=1; i<n; i++) {
            order.pb({ton[i].len, i});
            if (!ton[i].isClone)
                cnt[i] = 1;
        }
        // sort by len decreasingly
        sort(order.rbegin(), order.rend());
        for(auto [len, i] : order) {
            cnt[ton[i].link] += cnt[i];
        }
    }
    ll countPattern(string &p) { // O( p.size() )
        assert(!cnt.empty());
        ll cur = 0;
        for(auto c : p) {
            if (ton[cur].down.count(c)) {
                cur = ton[cur].down[c];
            }
            else return 0; // no match
        }
        return cnt[cur];
    }
 
    // p3. Find the first position in which occurred the pattern (0-idx)
    ll firstPattern(string &p) { // O( p.size() )
        ll cur = 0;
        for(auto c : p) {
            if (ton[cur].down.count(c)) {
                cur = ton[cur].down[c];
            }
            else return -1; // no match
        }
        ll sz = p.size();
        return ton[cur].first_pos - sz + 1;
    }
}