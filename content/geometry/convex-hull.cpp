/**
 * Author: Errichto, PedroGallo
 * Date: 04/11/2024
 * Description: Compute the convex hull of a set of points
 * Time: O(n * log(n))
 * Status: copied from https://www.youtube.com/live/G9QTjWtK_TQ?si=D4dAAycxTJO2xPoA&t=7825
 */

// import point struct

vector<point> convex_hull(vector<point> v) {
    vector<point> hull;
    sort(begin(v), end(v));
    for(ll k=0; k<2; k++){
        ll S = size(hull);
        for(point next : v){
            while(size(hull) - S >= 2) {
                point prev = end(hull)[-2];
                point mid = end(hull)[-1];
                if(((mid-prev) ^ (next-prev)) < 0) break;
                hull.pop_back();
            }
            hull.push_back(next);
        }
        hull.pop_back();
        reverse(v.begin(), v.end());
    }
    return hull;
}