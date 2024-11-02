/**
 * Author: Wallace
 * Date: 01/11/2024
 * Description: Fraction Class
 * Time: O(1)
 * Status: Tested manually
*/

struct F {
    ll num = 0, den = 1;

    // whenever I create a new fraction, and after all operations
    // it will be automatically reduced
    void reduce() {
        ll g = gcd(num, den);
        num /= g;
        den /= g;
        // it will always force the negative sign to be at the numerator
        if (den < 0) num = -num, den = -den;
    }

    F(ll a = 0, ll b = 1) {
        assert(b != 0);
        num = a, den = b;
        reduce();
    }

    F& operator +=(F r) {
        // careful with overflows
        num = num * r.den + den * r.num;
        den = den * r.den;
        reduce();
        return *this;
    }
    friend F operator +(F l, F r) { return l += r; }

    F& operator -=(F r) {
        *this += F(-r.num, r.den);
        return *this;
    }
    friend F operator -(F l, F r) { return l -= r; }

    F& operator *=(F r) {
        num = num * r.num;
        den = den * r.den;
        reduce();
        return *this;
    }
    friend F operator *(F l, F r) { return l *= r; }

    F& operator /=(F r) {
        *this *= F(r.den, r.num);
        return *this;    
    }
    friend F operator /(F l, F r) { return l /= r; }

    // careful with overflows
    bool operator ==(F r) { return num*r.den == den*r.num; }

    bool operator !=(F r) { return num*r.den != den*r.num; }

    bool operator <(F r) { return num*r.den < den*r.num; }

    friend ostream& operator <<(ostream& out, F a) { 
        return out << a.num << "/" << a.den; 
    }

    // cin >> "num/den"
    friend istream& operator >>(istream& in, F& me) { 
        ll a, b; char c;
        in >> a >> c >> b;
        me = F(a, b);
        return in;
    }
};