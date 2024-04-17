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

    // problems that can be solved //

    // Check for occurrence of a pattern P
    // by returning the length of the longest prefix of P in S
    ll checkPattern(string &p) {
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
};