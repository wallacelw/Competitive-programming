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

## Equacao Diofantina Linear

Encontra solução para ax+by=g

```cpp
 
int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}
```