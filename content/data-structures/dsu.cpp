/**
 * Author: Wallace
 * Date: 06/02/2024
 * Description: Disjoint Set Union with path compression and tree balancing
 * Time: O(\alpha)
 */

struct DSU{
    vector<ll> group, card;
    DSU (ll n){
        n += 1; // 0-idx -> 1-idx
        group = vector<ll>(n);
        iota(group.begin(), group.end(), 0);
        card = vll(n, 1);
    }
    ll find(ll i){
        return (i == group[i]) ? i : (group[i] = find(group[i]));
    }
    // returns false if a and b are already in the same component
    bool join(ll a ,ll b){ 
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (card[a] < card[b]) swap(a, b);
        card[a] += card[b];
        group[b] = a;
        return true;
    }
};