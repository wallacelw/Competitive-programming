/**
 * Author: Wallace
 * Date: 27/02/2024
 * Description: Computes the min/max for a function that is monotonically increasing then decreasing 
 * or decreasing then increasing.
 * Time: O(N\log{N}_3)
 * Status: Tested (https://codeforces.com/contest/1933/problem/E)
 */

/*
Float and Min Version: Requires EPS (precision usually defined in the question text)
*/

ld f(ld d){
    // function here
}

// for min value
ld ternary_search(ld l, ld r){ 
    while(r - l > EPS){
        // divide into 3 equal parts and eliminate one side
        ld m1 = l + (r - l) / 3; 
        ld m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)){
            r = m2;
        }
        else {
            l = m1;
        }
    }
    return f(l); // check here for min/max
}
    

/*
Integer and Max Version:
*/

ll f(ll idx) {
    // function here
}

// for max value, using integer idx
ll ternary_search(ll l, ll r) {
    while(l <= r) {
        // divide into 3 equal parts and eliminate one side
        ll m1 = l + (r-l)/3;
        ll m2 = r - (r-l)/3;
        if(f(m1) < f(m2)) {
            l = m1+1;
        } 
        else {
            r = m2-1;
        }
    }
    return f(l); // check here for min/max
}
