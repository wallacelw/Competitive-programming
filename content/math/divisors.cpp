/**
 * Author: Wallace
 * Date: 05/11/2024
 * Description: Find all the divisors of a number N, and return them as a ordered vector.
 * Time: O(\sqrt{N})
 * Status: tested
 */

// return the list of divisors of val in O(sqrt(val))
// the divisors list has unique values and is ordered
vector<ll> divisors(ll val) {
    vector<ll> div, div2;
    for(ll i=1; i*i<=val; i++) {
        if (val % i == 0) {
            div.pb(i);
            if (val/i != i) div2.pb(val/i);
        } 
    }
    while(div2.size()) {
        div.pb(div2.back());
        div2.pop_back();
    }
    return div;
}