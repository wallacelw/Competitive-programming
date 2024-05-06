/**
 * Author: Bruno Monteiro, Wallace
 * Date: 22/04/2024
 * Description: Implicit Treap
 * Time: O(\log(n)) with high probability
 * Status: Tested(but it can be improved and the increment() function is not tested yet)
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
        void push() {
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
                    x->push();
                    sz += x->sz;
                    sum += x->sum;
                }
            }
        }
    };
 
    Node* root;
 
    Treap() { root = NULL; }
 
    // copy constructor to remind the user to not copy the treap object
    Treap(const Treap& t) { 
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
    ll size() { return size(root); } // maybe useless line of code

    // Supposes that l < r when merging
    void merge(Node*& x, Node* l, Node* r) { 
        if (!l or !r) return void(x = l ? l : r);
        l->push(), r->push();
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
        x->push();
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
 
    // increment value for [l, r] (not tested yet)
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

    // return in a vector all the elements in the treap, from left to right
    void inOrder(Node *u, vector<ll> &vec) {
        if (!u) return;
        u->push();
        // in-order
        inOrder(u->l, vec);
        vec.pb(u->val);
        inOrder(u->r, vec);
    }
    vector<ll> get() {
        vector<ll> vec;
        inOrder(root, vec);
        return vec;
    }
};