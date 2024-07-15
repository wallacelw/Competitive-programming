/**
 * Author: cp-algo
 * Date: 18/02/2024
 * Description: Solves the $ a*x + b*y = gcd(a, b) $ equation
 * Time: O(\log{ min(a, b) })
 */

// equation: a*x + b*y = gcd(a, b)
// input: (a, b)
// returns gcd of (a, b) 
// also computes &x and &y, which are passed by reference

ll extendedEuclid(ll a, ll b, ll &x, ll &y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = pair{x1, x - q * x1};
        tie(y, y1) = pair{y1, y - q * y1};
        tie(a1, b1) = pair{b1, a1 - q * b1};
    }
    return a1;
}

// returns val^(-1) (mod m)
// <=> gcd(val, m) == 1
ll inv(ll val, ll m) { 
    ll x, y;
    extendedEuclid(val, m, x, y);
    return ((x % m) + m) % m;;
}