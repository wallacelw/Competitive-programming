# Binary search

## Código:
```cpp
bool attribute(int a){
    return true;
}

int search(int l=0, int r=1e9, int ans=0){
    while(l <= r) {
        int mid = (l+r)/2;
 
        if(attribute(mid)) {
            ans = mid;
            l = mid+1;
        }
        else {
            r = mid-1;
        }
    }
    return ans;
}
```

## Problems

- Find an element in any monotonic function