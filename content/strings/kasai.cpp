/**
 * Author: Wallace, Tiagosf00
 * Date: 11/02/2024
 * Description: Creates the Longest Common Prefix array (LCP)
 * Time: O(N \log{N})
 * Status: Tested (https://cses.fi/problemset/result/8449721/)
 */

vector<ll> kasai(string s, vector<ll> sa) {
    ll n = s.size(), k = 0;
    vector<ll> ra(n), lcp(n);
    for (ll i = 0; i < n; i++) ra[sa[i]] = i;
 
    for (ll i = 0; i < n; i++, k -= !!k) {
        if (ra[i] == n-1) { k = 0; continue; }
        ll j = sa[ra[i]+1];
        while (i+k < n and j+k < n and s[i+k] == s[j+k]) k++;
        lcp[ra[i]] = k;
    }
    return lcp;
}