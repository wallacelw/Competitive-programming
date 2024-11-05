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

    Z& operator +=(Z r) {
        val += r.val;
        if (val >= P) val -= P;
        return *this;
    }
    friend Z operator +(Z l, Z r) { return l += r; }

    Z& operator -=(Z r) {
        val += P - r.val;
        if (val >= P) val -= P;
        return *this;
    }
    friend Z operator -(Z l, Z r) { return l -= r; }

    Z& operator *=(Z r) {
        val = (val * r.val) % P;
        return *this;
    }
    friend Z operator *(Z l, Z r) { return l *= r; }

    Z operator ^(ll i) const {
        Z ans = 1, aux = val;
        while(i) {
            if (i & 1) ans *= aux;
            aux *= aux;
            i >>= 1;
        }
        return ans;
    }

    Z& operator /=(Z r) {
        return *this *= r^(P-2);
    }
    friend Z operator /(Z l, Z r) { return l /= r; }

    bool operator ==(Z r) { return val == r.val; }

    bool operator !=(Z r) { return val != r.val; }

    friend ostream& operator <<(ostream& out, Z a) { return out << a.val; }

    friend istream& operator >>(istream& in, Z& a) {
        ll x; in >> x;
        a = Z(x);
        return in;
    }
};
using mint = Z<MOD>;