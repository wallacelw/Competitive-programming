## Matrix

### Matrix operations

```cpp
struct Matrix{
    vector<vll> M, IND;
    
    Matrix(vector<vector<int>> mat){
        M = mat;
    }
 
    Matrix(int row, int col, bool ind=0){
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

    Matrix operator +(const Matrix &B) const{ // A+B (sizeof(A) == sizeof(B))
        vector<vector<int>> ans(M.size(), vector<int>(M[0].size(), 0));
        for(int i=0; i<(int)M.size(); i++){
            for(int j=0; j<(int)M[i].size(); j++){
                ans[i][j] = M[i][j] + B.M[i][j];
            }
        }
        return ans;
    }
 
    Matrix operator *(const Matrix &B) const{ // A*B (A.column == B.row)
        vector<vector<int>> ans;
        for(int i=0; i<(int)M.size(); i++){
            vector<int> aux;
            for(int j=0; j<(int)M[i].size(); j++){
                int sum=0;
                for(int k=0; k<(int)B.M.size(); k++){
                    sum = sum + (M[i][k]*B.M[k][j]);
                }
                aux.push_back(sum);
            }
            ans.push_back(aux);
        }
        return ans;
    }

    Matrix operator ^(const int n) const{ // Need identity Matrix
        if (n == 0) return IND;
        if (n == 1) return (*this);
        Matrix aux = (*this) ^ (n/2);
        aux = aux * aux;
        if(n % 2 == 0)
            return aux;
        else{
            return (*this) * aux;
        }
    }
};
```

### Another Version with separated Identity

```cpp
Matrix IdentityM(5, 5, 1);
struct Matrix{
    vector<vll> M;
    
    Matrix(vector<vll> mat) {
        M = mat;
    }
    
    // identity == 0 => Empty matrix constructor
    // identity == 1 => generates a Identity Matrix
    Matrix(ll row, ll col, bool identity = 0){
        M.assign(row, vll(col, 0));

        if (identity) // row == col
            for(ll i=0; i<row; i++)
                M[i][i] = 1;
    }

    // A+B ; needs (sizeof(A) == sizeof(B))
    Matrix operator +(const Matrix &B) const{
        ll row = M.size(); ll col = M[0].size();

        Matrix ans(row, col);

        for(ll i=0; i<row; i++){
            for(ll j=0; j<col; j++){
                ans.M[i][j] = (M[i][j] + B.M[i][j]) % MOD;
            }
        }
        return ans;
    }
    // A*B (A.column == B.row)
    Matrix operator *(const Matrix &B) const{ 
        ll rowA = M.size(); ll colB = B.M[0].size();
        ll colA; ll rowB = colA = M[0].size();

        Matrix ans(rowB, colA);

        for(ll i=0; i<rowA; i++){
            for(ll j=0; j<colA; j++){
                ll sum=0;
                for(ll k=0; k<rowB; k++){
                    sum += (M[i][k] * B.M[k][j]) % MOD;
                    sum %= MOD;
                }
                ans.M[i][j] = sum;
            }
        }
        return ans;
    }

    Matrix operator ^(const ll n) const{ // Need identity Matrix
        if (n == 0) return IdentityM;
        if (n == 1) return (*this);
        Matrix aux = (*this) ^ (n/2);
        aux = aux * aux;
        if(n % 2 == 0) return aux;
        else return (*this) * aux;
    }
};
```