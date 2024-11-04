/**
 * Author: PedroGallo
 * Date: 04/11/2024
 * Description: return if a point is inside a polygon using Winding number
 * -1: inside
 *  0: boundary
 *  1: outside
 * Time: O(n)
 * Status: tested in https://acm.timus.ru/problem.aspx?space=1&num=1599
 */

// import point struct

int inside_poly(const point &b, const vector<point> &poly){
    int N = poly.size(), winding = 0;
    for(int i=0; i<N; i++){
        int j = (i+1)%N;
        point e = poly[j] - poly[i];
        point r1 = b - poly[i];
        point r2 = b - poly[j];
        if((e^r1) == 0 and e*r1 >= 0 and (e*(-1))*r2 >= 0){
            return 0;
        }
        
        if(poly[i].y <= b.y and b.y < poly[j].y and (e^r1) > 0){
            winding++;
        }
        else if(poly[j].y <= b.y and b.y < poly[i].y and ((e*(-1))^r2) > 0){
            winding--;
        }
    }
    
    if(winding%2 == 0){
        return -1;
    }
    return 1;
}
