/**
 * Author: PedroGallo
 * Date: 04/11/2024
 * Description: return if a point is inside a convex polygon
 * Polygon need to be rotated such: poly[0] = (the point with lower (x, y))
 * -1: inside
 *  0: boundary
 *  1: outside
 * Time: O(log(n))
 * Status: tested
 */

// import point struct

int sgn(int b){
    if(b > 0){
        return 1;
    }
    else if(b < 0){
        return -1;
    }
    return 0;
}

int inside_tri(const point &b, const array<point, 3> &tri){
    int N = 3, signs[3];
    for(int i=0; i<N; i++){
        point v = tri[(i+1)%N] - tri[i];
        point r = b - tri[i];
        signs[i] = sgn(v^r);
    }

    if(signs[0] == signs[1] and signs[1] == signs[2]){
        return -1;
    }
    for(int i=0; i<N; i++){
        if(signs[i] * signs[(i+1)%N] == -1){
            return 1;
        }
    }
    return 0;
}

int inside_poly_conv(const point &b, const vector<point> &poly){ // rotate poly such that: poly[0] = min(point in poly)
    if(b.x < poly[0].x){
        return 1;
    }
    int N = poly.size();

    int l = 1, r = N-2, ans = 1;
    while(l <= r){
        int mid = (l + r)/2;
        point v = poly[mid] - poly[0];
        point e = b - poly[0];
        if((v^e) >= 0){
            l = mid + 1;
            ans = mid;
        }
        else{
            r = mid - 1;
        }
    }

    array<point, 3> tri = {poly[0], poly[ans], poly[ans+1]};
    return inside_tri(b, tri);
}
