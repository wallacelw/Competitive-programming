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
    bool join(ll a, ll b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (card[a] < card[b]) swap(a, b);
        card[a] += card[b];
        group[b] = a;
        return true;
    }
};