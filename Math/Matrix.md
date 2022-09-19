# Matrix

## Matrix operations

```cpp
struct matrix{
    vector<vector<int>> M, IND;
 
    matrix(vector<vector<int>> mat){
        M = mat;
    }
 
    matrix(int row, int col, bool ind=0){
        M = vector<vector<int>>(row, vector<int>(col, 0));
        if(ind){
            vector<int> aux(row, 0);
            for(int i=0; i<row; i++){
                aux[i] = 1;
                IND.push_back(aux);
                aux[i] = 0;
            }
        }
    }

    matrix operator +(const matrix &B) const{ // A+B (sizeof(A) == sizeof(B))
        vector<vector<int>> ans(M.size(), vector<int>(M[0].size(), 0));
        for(int i=0; i<M.size(); i++){
            for(int j=0; j<M[i].size(); j++){
                ans[i][j] = M[i][j] + B.M[i][j];
            }
        }
        return ans;
    }
 
    matrix operator *(const matrix &B) const{ // A*B (A.column == B.row)
        vector<vector<int>> ans;
        for(int i=0; i<M.size(); i++){
            vector<int> aux;
            for(int j=0; j<M[i].size(); j++){
                int sum=0;
                for(int k=0; k<B.M.size(); k++){
                    sum = sum + (M[i][k]*B.M[k][j]);
                }
                aux.push_back(sum);
            }
            ans.push_back(aux);
        }
        return ans;
    }
 
    matrix operator ^(const int n) const{ // Need identity matrix
        if (n == 0) return IND;
        if (n == 1) return (*this);
        matrix aux = (*this) ^ (n/2);
        aux = aux * aux;
        if(n % 2 == 0)
            return aux;
        else{
            return (*this) * aux;
        }
    }
 
};
```