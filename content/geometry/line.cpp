/**
 * Author: Tiago, Wallace
 * Date: 01/04/2024
 * Description: Line struct for line operations
 * Time: O(1)
 * Status: copied from tiagosf00, tested for int
 */

template<class T> struct L {
    point p1, p2;
    T a, b, c; // ax+by+c = 0;

    // y-y1 = ((y2-y1)/(x2-x1))(x-x1)
    L(point pp1=0, point pp2=0) : p1(pp1), p2(pp2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = p1 ^ p2;
    }

    T eval(point p) {
        return a*p.x + b*p.y + c;
    }

    bool inside(point p) { // reta
        return eq(eval(p), T(0));
    }

    point normal() {
        return point(a, b);
    }

    bool insideSeg(point p) { // segmento [p1, p2]
        return ( ((p1-p) ^ (p2-p)) == 0 and ((p1-p) * (p2-p)) <= 0 );
    }
};
using line = L<ll>;
// using line = L<ld>;