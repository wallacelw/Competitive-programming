/**
 * Author: Quirino, Wallace
 * Date: 31/03/2024
 * Description: mint struct for modular arithmetic operations
 * Time: O(1) for most operations, O(log(n)) for division and exponentiation
 * Status: Not stress tested, but tested in multiple occasions
*/

// supports operations between int/ll and mint,
// and it will return a mint object independently of the order of operations
template<ll P> struct Z {
    ll val;

    Z(ll a = 0) {
        val = a % P;
        if (val < 0) val += P;
    }

    Z& operator +=(Z rhs) {
        val += rhs.val;
        if (val >= P) val -= P;
        return *this;
    }
    friend Z operator +(Z lhs, Z rhs) { return lhs += rhs; }

    Z& operator -=(Z rhs) {
        val += P - rhs.val;
        if (val >= P) val -= P;
        return *this;
    }
    friend Z operator -(Z lhs, Z rhs) { return lhs -= rhs; }

    Z& operator *=(Z rhs) {
        val = (val * rhs.val) % P;
        return *this;
    }
    friend Z operator *(Z lhs, Z rhs) { return lhs *= rhs; }

    Z fexp(Z x, ll i) {
        if (i == 0) return 1;
        if (i == 1) return x;
        Z m = fexp(x, i/2);
        m *= m;
        if (i & 1) return m * x;
        else return m;
    }

    Z& operator /=(Z rhs) {
        return *this *= fexp(rhs, P-2);
    }
    friend Z operator /(Z lhs, Z rhs) { return lhs /= rhs; }

    bool operator ==(Z rhs) { return val == rhs.val; }

    bool operator !=(Z rhs) { return val != rhs.val; }

    friend ostream& operator <<(ostream& out, Z a) { return out << a.val; }

    friend istream& operator >>(istream& in, Z& a) {
        ll x; in >> x;
        a = Z(x);
        return in;
    }
};
using mint = Z<MOD>;