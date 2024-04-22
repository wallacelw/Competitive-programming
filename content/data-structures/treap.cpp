/**
 * Author: Bruno Monteiro, Wallace
 * Date: 22/04/2024
 * Description: Implicit Treap
 * Time: O(log{n}) with high probability
 * Status: Tested(but it may have memory leakage)
 */

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
struct Treap { // Implicit 0-idx
    struct Node {
        Node *l = NULL, *r = NULL;
        ll val, p;
        ll sz, sum, lazy;
        bool rev = false;
        Node(ll v) : val(v), p(rng()) {
            sz = 1, sum = val, lazy = 0;
        }
        void prop() {
            if (lazy) {
                val += lazy, sum += lazy*sz;
                if (l) l->lazy += lazy;
                if (r) r->lazy += lazy;
            }
            if (rev) {
                swap(l, r);
                if (l) l->rev ^= 1;
                if (r) r->rev ^= 1;
            }
            lazy = 0, rev = 0;
        }
        void update() {
            sz = 1, sum = val;
            for(auto x : {l, r}) {
                if (x) {
                    x->prop();
                    sz += x->sz;
                    sum += x->sum;
                }
            }
        }
    };
 
    Node* root;
 
    Treap() { root = NULL; }
 
    Treap(const Treap& t) { // copy constructor
        throw logic_error("Nao copiar a Treap!");
    }
 
    ~Treap() { // deconstructor
        vector<Node*> q = {root};
        while (q.size()) {
            Node* x = q.back(); q.pop_back();
            if (!x) continue;
            q.pb(x->l), q.pb(x->r);
            delete x;
        }
    }
 
    ll size(Node* x) { return x ? x->sz : 0; }
    ll size() { return size(root); }

    // Supposes that l < r
    void merge(Node*& x, Node* l, Node* r) { 
        if (!l or !r) return void(x = l ? l : r);
        l->prop(), r->prop();
        if (l->p > r->p) {
            merge(l->r, l->r, r);
            x = l;
        }
        else {
            merge(r->l, l, r->l);
            x = r;
        }
        x->update();
    }
 
    // split into [0, mid), [mid, n)
    // with size(left) = mid, size(right) = n-mid
    void split(Node* x, Node*& l, Node*& r, ll mid) {
        if (!x) return void(r = l = NULL);
        x->prop();
        if (size(x->l) < mid) {
            split(x->r, x->r, r, mid - size(x->l) - 1);
            l = x;
        }
        else {
            split(x->l, l, x->l, mid);
            r = x;
        }
        x->update();
    }
 
    // insert new element with val=v into the rightmost position
    void insert(ll v) {
        Node* x = new Node(v);
        merge(root, root, x);
    }
 
    // get the query value for [l, r]
    ll query(ll l, ll r) {
        Node *L, *M, *R;
        split(root, M, R, r+1), split(M, L, M, l);
        ll ans = M->sum;
        merge(M, L, M), merge(root, M, R);
        return ans;
    }
 
    // increment value for [l, r]
    void increment(ll l, ll r, ll s) {
        Node *L, *M, *R;
        split(root, M, R, r+1), split(M, L, M, l);
        M->lazy += s;
        merge(M, L, M), merge(root, M, R);
    }
 
    // reverses interval [l, r] to [r, l]
    void reverse(ll l, ll r) {
        Node *L, *M, *R;
        split(root, M, R, r+1), split(M, L, M, l);
        M->rev ^= 1;
        merge(M, L, M), merge(root, M, R);
    }
};
 
vector<ll> dfs(Treap::Node *root) {
    vector<ll> ans;
    function<void (Treap::Node*)> print = [&](Treap::Node *u) {
        if (!u) return;
        u->prop();
        print(u->l);
        ans.pb(u->val);
        print(u->r);
    };
    print(root);
    return ans;
}