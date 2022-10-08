# Merge sort

```cpp
void merge(vector<int> &v, int l, int mid, int r){
    int i=l, j=mid+1;
    vector<int> ans;
 
    while(i <= mid or j <= r){

        if(j > r or v[i] <= v[j]){
            ans.push_back(v[i]);
            i++;
        }
        if(i > mid or v[j] < v[i]){
            ans.push_back(v[j]);
            j++;
        }
    }

    for(int i=l; i<=r; i++)
        v[i] = ans[i-l];
}

void merge_sort(vector<int> &v, vector<int> &ans, int l, int r){
    if(l==r){
        ans[l] = v[l];
        return;
    }


    int mid = (l+r)/2;
    merge_sort(v, ans, l, mid);
    merge_sort(v, ans, mid+1, r);
    merge(ans, l, mid, r);

    return;
}
```