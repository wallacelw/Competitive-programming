/**
 * Author: Bruno Monteiro, Wallace
 * Date: 12/05/2024
 * Description: Given a vector of directed edges with weights and a root, 
 * compute the cost of the directed minimum spanning tree (all nodes reachable from root);
 * or return INF if it doesn't exist.
 * Time: O(m \log(n)) for sparse graphs, O(n^2) for dense graphs; 
 * Status: Tested (https://codeforces.com/gym/102483/my, F)
*/

using T = array<ll, 3>;

struct directedMST { // 0-idx
    struct Node {
        pair<ll, ll> val;
        ll lazy = 0;
        Node *l = NULL, *r = NULL;

        Node() {}
        Node(ll a, ll b) : lazy(0), l(NULL), r(NULL) { val = {a, b}; }

        void push() {
            val.ff += lazy;
            if (l) l->lazy += lazy;
            if (r) r->lazy += lazy;
            lazy = 0;
        }
    };

    void erase(Node *i) {
        if (i) {
            erase(i->l), erase(i->r);
            delete i;
        }
    }

    pair<ll, ll> pop(Node* &i) {
        i->push();
        auto ret = i->val;
        Node *tmp = i;
        join(i->l, i->r);
        i = i->l;
        if (i) i->lazy -= ret.ff;
        delete tmp;
        return ret;
    }

    ll n, root;
    vector<T> edges;
    vector<ll> group;
    vector<Node*> h;

    ll find(ll i) {
        return (group[i] == i) ? i : (group[i] = find(group[i]));
    }

    void join(Node* &a, Node* b) {
        if (!a) swap(a, b);
        if (!b) return;
        a->push(), b->push();
        if (a->val > b->val) swap(a, b);
        join((rand() % 2) ? a->l : a->r, b);
    }

    // 0-idx [0, n), edges = {u, v, w}, from U, to V, with weight W 
    directedMST(ll n_, ll root_, vector<T> &edges_) 
        : n(n_), root(root_), edges(edges_), group(n), h(n) { 
        iota(group.begin(), group.end(), 0);
    }

    ~directedMST() {
        for(auto i : h) erase(i);
    };

    ll solve() {
        for(auto [u, v, w] : edges) {
            join(h[v], new Node(w, u));
        }

        vector<ll> p(n, -1), path(n);
        p[root] = root;
        ll ans = 0;

        for(ll i=0; i<n; i++) {
            ll u = i, at = 0;
            while(p[u] == -1) {
                if (!h[u]) return INF;

                path[at++] = u, p[u] = i;
                auto [mn, v] = pop(h[u]);
                ans += mn;

                if (p[u = find(v)] == i) {
                    while(find(v = path[--at]) != u) {
                        join(h[u], h[v]);
                        h[v] = NULL;
                        group[find(v)] = u;
                    }
                    p[u] = -1;
                }
            }
        }

        return ans;
    }
};