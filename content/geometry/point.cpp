/**
 * Author: Tiago, Quirino, Wallace
 * Date: 01/04/2024
 * Description: Point struct for point operations, supports floating points and integers
 * Time: O(1)
 * Status: Not fully tested
 */

const ld EPS = 1e-9;

// T can be int, long long, float, double, long double
template<class T> struct P {
    T x, y;
    
    P(T xx=0, T yy=0): x(xx), y(yy) {}

    P operator +(P const& o) const { return { x+o.x, y+o.y }; }
    P operator -(P const& o) const { return { x-o.x, y-o.y }; }
    P operator *(T const& t) const { return { x*t, y*t }; }
    P operator /(T const& t) const { return { x/t, y/t }; }
    T operator *(P const& o) const { return x*o.x + y*o.y; }
    T operator ^(P const& o) const { return x*o.y - y*o.x; }

    bool eq(T a, T b) {
        if (is_integral<T>::value) return a == b;
        else return abs(a-b) <= EPS;
    }

    bool operator <(P const& o) const {
        if (!eq(x, o.x)) return x < o.x;
        if (!eq(y, o.y)) return y < o.y;
        return false;
    }

    bool operator ==(P const& o) const {
        return eq(x, o.x) and eq(y, o.y);
    }

    bool operator !=(P const& o) const {
        return !(*this == o);
    }

    friend istream& operator >>(istream& in, P &p) {
        return in >> p.x >> p.y;
    }

    friend ostream& operator <<(ostream& out, P const& p) {
        return out << p.x << ' ' << p.y;
    }
};
using point = P<ll>;
// using point = P<ld>;