/**
 * Author: Wallace
 * Date: 01/08/2024
 * Description: count the numbers with bit b set in range [0, n] and [l, r]
 * Time: O(1)
*/

// count of numbers with bit b set in range [0, n]
ll sum(ll n, ll b) {
    ll t = 1LL << (b+1);
    ll ans = ((n+1)/t) * (t/2);
    ll last = n + 1 - ((n+1)/t) * t;
    ll ones = max(0LL, last - t/2);
    return ans + ones;
}

// count of numbers with bit b set in range [l, r]
ll range(ll l, ll r, ll b) {
    ll ans = sum(r, b);
    if (l) ans -= sum(l-1, b);
    return ans;
}