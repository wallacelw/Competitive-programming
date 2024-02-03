## Point Struct for 2D

ld behaviour not tested!

```cpp
typedef ll unit;
bool eq(unit a, unit b){ return abs(a - b) <= EPS; }

struct P {
    unit x, y;
    P(unit xx=0, unit yy=0): x(xx), y(yy){}
    P operator +(const P& b) const { 
        return P{x + b.x, y + b.y}; 
    }
    P operator -(const P& b) const { 
        return P{x - b.x, y - b.y};
    }
    P operator *(unit t) const {
        return {x*t, y*t};
    }
    P operator /(unit t) const { 
        return {x/t, y/t}; 
    }
    unit operator *(const P& b) const { 
        return x*b.x + y*b.y; 
    }
    unit operator ^(const P& b) const {
        return x*b.y - y*b.x;
    }
    bool operator <(const P& b) const {
        return (eq(x, b.x) ? y < b.y : x < b.x);
    }
    bool operator ==(const P& b) const {
        return eq(x, b.x) and eq(y, b.y);
    }
    unit dist(P b) {
        return ((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y));
    }
    unit dot(const P& b, const P& c) const{
        return (b-*this) * (c-*this);
    }
    unit cross(const P& b, const P& c) const{
        return (b-*this) ^ (c-*this);
    }
};
```