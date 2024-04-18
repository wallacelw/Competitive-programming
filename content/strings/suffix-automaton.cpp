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

                while (p != -1 and ton[p].down[c] == q) {
                    ton[p].down[c] = clone;
                    p = ton[p].link;
                }
                ton[cur].link = ton[q].link = clone;
            }
        }
        last = cur;
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
};