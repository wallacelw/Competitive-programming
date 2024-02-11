/**
 * Author: Wallace, Tiagosf00
 * Date: 11/02/2024
 * Description: Creates the Suffix Array
 * Time: O(N \log{N})
 * Status: Tested (https://cses.fi/problemset/result/8449721/)
 */

vector<ll> suffixArray(string s) {
    s += "!";
    ll n = s.size(), N = max(n, 260LL);
    vector<ll> sa(n), ra(n);
    for (ll i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
 
    for (ll k = 0; k < n; k ? k *= 2 : k++) {
        vector<ll> nsa(sa), nra(n), cnt(N);
 
        for (ll i = 0; i < n; i++) nsa[i] = (nsa[i]-k+n)%n, cnt[ra[i]]++;
        for (ll i = 1; i < N; i++) cnt[i] += cnt[i-1];
        for (ll i = n-1; i+1; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];
 
        for (ll i = 1, r = 0; i < n; i++) nra[sa[i]] = r += ra[sa[i]] !=
            ra[sa[i-1]] or ra[(sa[i]+k)%n] != ra[(sa[i-1]+k)%n];
        ra = nra;
        if (ra[sa[n-1]] == n-1) break;
    }
    return vector<ll>(sa.begin()+1, sa.end());
}