# Convex Hull

**Complexity:** O(n * log (n))

## Código:
```cpp
struct point{
    int x, y;
    int ind;
 
    point operator -(const point& b) const{
        return point{x - b.x, y - b.y};
    }
 
    int operator ^(const point& b) const{ // cross product
        return x*b.y - y*b.x;
    }

    int cross(const point& b, const point&c) const{ // cross product with diferent base
        return (b - *this) ^ (c - *this);
    }
 
    bool operator <(const point& b) const{
        return make_pair(x,y) < make_pair(b.x,b.y);
    }

};
 
vector<point> convex_hull(vector<point>& v){
    vector<point> hull;
    sort(v.begin(), v.end());

    for(int rep=0; rep<2; rep++){
        int S = hull.size();
        for(point next : v){

            while(hull.size() - S >= 2){
                point prev = hull.end()[-2]; // hull[size - 2]
                point mid = hull.end()[-1]; // hull[size - 1]
                if(prev.cross(mid, next) <=0) // 0 collinear
                    break;
                hull.pop_back();
            }

            hull.push_back(next);
        }

        hull.pop_back();
        reverse(v.begin(), v.end());
    }
    return hull;
}
```
