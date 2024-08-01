/**
 * Author: Wallace, Quirino
 * Date: 01/08/2024
 * Description: basic operations for combinatorics problems under a certain modulo
 * Time: O(n) to construct, ~O(1) operations
 * Status: permutations and arrangements needs to be verified
*/

// remeber to import mint struct !!
struct Combinatorics {
    vector<mint> fact, ifact;

    Combinatorics(ll n) : fact(n+1), ifact(n+1) { // inclusive n
        fact[0] = 1;
        for (ll i=1; i<=n; i++) fact[i] = fact[i-1] * i;

        ifact[n] = 1 / fact[n];
        for (ll i=n; i>0; i--) ifact[i-1] = ifact[i] * i;
    }

    // Combination, "Combinacao"
    // n objects to place in k spaces
    // the order doesn't matter, so we consider the re-orderings
    // = n! / (k! * (n-k)!) 
    mint C(ll n, ll k) {
        if (k < 0 or n < k) return 0;
        return fact[n] * ifact[k] * ifact[n-k];
    }

    // Permutation, "Permutacao"
    // n objects to place in n spaces
    // = n!
    mint P(ll n) {
        if (n < 0) return 0;
        return fact[n];
    }

    // Permutation with Repetition, "Permutacao com repeticao"
    // Also called: Multinomial coefficients
    // n objects to place in n spaces
    // some objects are equal
    // therefore, we consider the possible re-orderings
    // = n! / (k1! k2! k3!)
    mint PR(ll n, vector<ll> vec) {
        if (n < 0) return 0;
        mint ans = fact[n];
        for(auto val : vec) ans *= ifact[val];
        return ans;
    }

    // Arrangement, "Arranjo Simples"
    // n objects to place in k spaces (k < n)
    // n * (n-1) * ... * (n-k+1)
    // = n! / (n-k)!
    mint A(ll n, ll k) {
        if (n < 0) return 0;
        return fact[n] * ifact[n-k];
    }

    // Stars and Bars, "Pontos e Virgulas"
    // n stars to distribute among
    // k distint groups, that can contain 0, 1 or more stars
    // separated by k-1 bars 
    // = (n+k-1)! / ( n! * (k-1)! ) 
    mint SB(ll n, ll k) {
        if (k == 0) {
            if (n == 0) return 1;
            else return 0;
        }
        return C(n + k - 1, k - 1);
    }

    // a derangement is a permutation of the elements of a set 
    // in which no element appears in its original position
    // In other words, a derangement is a permutation that has no fixed points.
    // derangement(n) = subfactorial(n) = !n
    // !n = (n-1) * ( !(n-1) + !(n-2) ), for n >= 2
    // !1 = 0, !0 = 1
    vector<mint> subfact;
    void computeSubfactorials(ll n) {
        subfact.assign(n+1, 0);
        subfact[0] = 1;
        subfact[1] = 0;

        for(ll i=2; i<=n; i++) {
            subfact[i] = (i-1) * (subfact[i-1] + subfact[i-2]);
        }
    }
    // remeber to compute subfactorials first !!
    mint derangement(ll n) { 
        if (n < 0) return 0;
        return subfact[n];
    }
};
Combinatorics op(MAX); // MAX = inclusive max_value for fact[]