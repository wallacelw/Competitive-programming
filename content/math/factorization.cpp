/**
 * Author: Wallace
 * Date: 01/11/2024
 * Description: Factorization; primes are given in crescent order with smallest prime.
 * Time: O(\sqrt{n}) for trial division; 
 * O(\log2(n)) using smallest prime;
 * Status: Tested (https://codeforces.com/contest/895/my)
 */

vector<ll> factorization(ll n){ // O(sqrt(n))
    vector<ll> factors;
    for(auto p : prime){
        if (p*p > n) break;
        while(n % p == 0){
            factors.pb(p);
            n /= p;
        }
    }
    if (n > 1) factors.pb(n);
    return factors;
}

// import linear sieve 
vector<ll> factorization(ll val) { // log2(val)
    vector<ll> factors;
    while(val > 1) {
        factors.pb(sp[val]);
        val /= sp[val];
    }
    return factors;
}

// import linear sieve
// {prime, multiplicity} 
vector<pll> factorization(ll val) { // log2(val)
    vector<pll> factors;
    while(val > 1) {
        if (factors.empty() or factors.back().first != sp[val]) {
            factors.pb({sp[val], 1});
        }
        else {
            auto [a, b] = factors.back();
            factors.pop_back();
            factors.pb({a, b+1});
        }
        val /= sp[val];
    }
    return factors;
}
