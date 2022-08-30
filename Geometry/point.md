# Point struct

## Código:
```cpp
struct point{
    int x, y;
    int ind;
 
    point operator -(const point& b) const{
        return point{x - b.x, y - b.y};
    }

    point operator +(const point& b) const{
        return point{x + b.x, y + b.y};
    }

    int operator *(const point& b) const{ // dot product
        return x*b.y + y*b.x;
    }
 
    int operator ^(const point& b) const{ // cross product
        return x*b.y - y*b.x;
    }

    int dot(const point& b, const point&c) const{ // dot product with diferent base
        return (b - *this) * (c - *this);
    }

    int cross(const point& b, const point&c) const{ // cross product with diferent base
        return (b - *this) ^ (c - *this);
    }
 
    bool operator <(const point& b) const{
        return make_pair(x,y) < make_pair(b.x,b.y);
    }

    bool operator ==(const point &o) const{
        return (x == o.x) and (y == o.y);
    }

};
```