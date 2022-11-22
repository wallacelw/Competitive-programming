## Closest-point (Divide and conquer)

```cpp
int solve(vector<point> x_s, vector<point> y_s){
    int n = x_s.size();
 
    if(n < 4){
        int d = x_s[0].dist(x_s[1]);
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++)
                d = min(d, x_s[i].dist(x_s[j]));
        }
        return d;
    }
 
    int mid = n/2;
    vector<point> x_sl(x_s.begin(), x_s.begin()+mid);
    vector<point> x_sr(x_s.begin()+mid, x_s.end());
    vector<point> y_sl, y_sr;
    for(auto p: y_s){
        if(p.x <= x_s[mid].x)
            y_sl.push_back(p);
        else
            y_sr.push_back(p);
    }
 
    int dl = solve(x_sl, y_sl);
    int dr = solve(x_sr, y_sr);


    // Merge !!!
    int d = min(dl, dr);
 
    vector<point> possible;
    for(auto p: y_s){
        if(x_s[mid].x-d < p.x and p.x < x_s[mid].x+d)
            possible.push_back(p);
    }
 
    n = possible.size();
    for(int i=0; i<n; i++){
        for(int j=1; (j<7 and j+i<n); j++){
            d = min(d, possible[i].dist(possible[i+j]));
        }
    }
 
    return d;
}
```