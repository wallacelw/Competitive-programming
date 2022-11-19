## Binary search

Finds the first element that changes value in any monotonic function

```cpp
bool attribute(int a){
    // add code here!!!!!
    return true;
}

int search(int l=0, int r=1e9, int ans=0){
    while(l <= r) { // [l; r]
        int mid = (l+r)/2;
 
        if(attribute(mid)) { // [mid; r]
            ans = mid;
            l = mid+1;
        }
        else { // [l; mid]
            r = mid-1;
        }
    }
    return ans;
}
```

- 