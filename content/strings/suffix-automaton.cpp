/**
 * Author: CP-algo, Wallace
 * Date: 17/04/2024
 * Description: Suffix automaton, each node represents a set of end-pos equivalent substrings.
 * Time: O(n log{k}), n = s.size(), k = characters used
 * Status: Tested in CSES
*/

struct SuffixAutomaton {
    struct State {
        ll len = 0, link = 0; // link = the state id connected by the uplink
        map<char, ll> down = {}; // ids of connected states below

        // extra for problems {2, 3}
        bool isClone = false;
        ll first_pos = -1;
        //
    };

    ll n = 1; // number of states
    vector<State> ton; // short for automaton :D

    SuffixAutomaton(string &s) {
        ton.pb( {0, -1} ); // root = 0
        for(auto c : s) add(c);
    }

    ll last = 0; // last state's id
    void add(char c) {
        ton.pb( {ton[last].len+1} );
        ll cur = n++;
        
        // extra for problems {3}
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

                // extra for problems {2}
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

    // problems that can be solved //

    // 1. Check for occurrence of a pattern P
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

    // 2. Count the numbers of occurrences of a pattern P
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

    // 3. Find the first position in which occurred the pattern (0-idx)
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
};
