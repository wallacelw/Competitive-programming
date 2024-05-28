/**
 * Author: Jose Leite (aka, chico nson), Wallace
 * Date: 27/05/2024
 * Description: É aho tbm porra
 * Time: O(n) add(), O(n Alpha) build() 
 * Status: Tested (https://cses.fi/problemset/result/9349972/)
 */

// obs: O(alphabet) is considered constant
const ll alphabet = 27; // index #26 = char('{') (separator)
 
struct Aho {
    struct State {
        // suffix link is the longest proper suffix
        // exit link is the next marked terminal node in the suffix link path
        ll link = 0, exit = 0, depth = 0;
        vector<ll> vec;
        bool term = 0; // isTerminal
        array<ll, alphabet> down = {}; // 0 => non existent edge
 
        ll& operator [](const char &c) {
            return down[c-'a'];
        }
    };
 
    ll n = 2; // number of states
    vector<State> t; // tree
 
    // root = node 1, root.link = 1
    Aho() : t(2) {}
 
    void add(string &s, ll val) {
        ll u = 1, h = 1;
        for(auto c : s) {
            if (!t[u][c]) {
                t[u][c] = n++;
                t.pb(State{});
            }
            u = t[u][c];
            t[u].depth = h++;
        }
        t[u].term = true;
        t[u].vec.pb(val);
    }
 
    void build() { // O(n * alphabet)
        for(ll i=1; i<n; i++) {
            t[i].link = 1;
        }
        queue<ll> q; q.push(1);
        while(q.size()) { // bfs
            auto u = q.front(); q.pop();
            for(ll i=0; i<alphabet; i++) {
                char c = char('a' + i);
                if (t[u][c]) {
                    auto v = t[u][c]; q.push(v);
                    if (u != 1) {
                        auto &link = t[v].link;
                        link = t[t[u].link][c];
                        t[v].exit = (t[link].term) ? link : t[link].exit;
                    }
                }
                // if there are no direct edges, use suffix link
                else if (u != 1) {
                    t[u][c] = t[t[u].link][c];
                }
                else { // root
                    t[u][c] = 1;
                }
            }
        }
    }
};
