/**
 * Author: Errichto, PedroGallo
 * Date: 04/11/2024
 * Description: Compute the convex hull of a set of points
 * Time: O(n * log(n))
 * Status: copied from https://www.youtube.com/live/G9QTjWtK_TQ?si=D4dAAycxTJO2xPoA&t=7825
 */

// import point struct

vector<point> convex_hull(vector<point>& v){
    vector<point> hull;
    sort(v.begin(), v.end());

    for(int rep=0; rep<2; rep++){
        int S = hull.size();
        for(point next : v){
            while(hull.size() - S >= 2){
                point prev = hull.end()[-2];
                point mid = hull.end()[-1];
                if(prev.cross(mid, next) < 0){
                    break;
                }
                hull.pop_back();
            }

            hull.push_back(next);
        }

        hull.pop_back();
        reverse(v.begin(), v.end());
    }
    return hull;
}
