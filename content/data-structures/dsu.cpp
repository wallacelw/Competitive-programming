/**
 * Author: Wallace
 * Date: 06/02/2024
 * Description: Disjoint Set Union with path compression and tree balancing
 * Time: O(\alpha)
 * Status: tested!
 */

struct DSU {
    vector<ll> group, card;

    DSU (ll n) : group(n+1), card(n+1, 1) { // 1-idx
        iota(group.begin(), group.end(), 0);
    }

    ll find(ll i) {
        return (i == group[i]) ? i : (group[i] = find(group[i]));
    }
    
    // returns false if a and b are already in the same component
    bool join(ll a ,ll b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (card[a] < card[b]) swap(a, b);
        card[a] += card[b];
        group[b] = a;
        return true;
    }
};

// with rollback and numbers of comps
// without path compression, therefore O(log n)
struct DSU { 
    vector<ll> group, card;
    vector<pair<ll &, ll>> history;
    ll comps;

    DSU (ll n) : group(n+1), card(n+1, 1) { // 1-idx
        iota(group.begin(), group.end(), 0);
        comps = n; // don't include 0
    }

    ll find(ll i){
        return (i == group[i]) ? i : find(group[i]);
    }

    void join(ll a ,ll b){ 
        a = find(a), b = find(b);
        if (a == b) return;

        if (card[a] < card[b]) swap(a, b);

        history.pb({card[a], card[a]});
        history.pb({group[b], group[b]});
        history.pb({comps, comps});

        comps -= 1;
        card[a] += card[b];
        group[b] = a;
    } 

    ll snapshot() { return history.size(); }

    void rollback(ll until) { // restore to snapshot == until
        while(snapshot() > until) {
            history.back().ff = history.back().ss;
            history.pop_back();
        }
    }
};