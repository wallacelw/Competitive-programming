## Extended Euclidian Algorithm

**Computes the coeficients of this diofantine equation:**

a*x + b*y = gcd(a, b)

**Can be used to find the inverse multiplicative of a number if gcd(a, mod) == 1**

a * x + m * y = gcd(a, m)
a * x = 1 (mod m)

```cpp
// a*x + b*y = gcd(a, b)
ll extended_euclid(ll a, ll b, ll &x, ll &y) { 
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a/b);
    return g;
}
```