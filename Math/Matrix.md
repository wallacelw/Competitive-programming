## Matrix

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

#### Another Version with long long and MOD

```cpp
struct Matrix{
    vector<vll> M, Identity;
    
    Matrix(vector<vll> mat) {
        M = mat;
    }
    
    // identity == 0 => Empty matrix constructor
    // identity == 1 => also generates a Identity Matrix
    Matrix(ll row, ll col, bool identity = 0){
        M.assign(row, vll(col, 0));

        if (identity) { // row == col
            Identity.assign(row, vll(col, 0));
            for(ll i=0; i<row; i++)
                Identity[i][i] = 1;
        }
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
        ll rowA = M.size();
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
        if (n == 0) return Identity;
        if (n == 1) return (*this);
        Matrix aux = (*this) ^ (n/2);
        aux = aux * aux;
        if(n % 2 == 0) return aux;
        else return (*this) * aux;
    }
};
```

#### Usage

For faster linear recurrence computation with matrix exponentiation. 

Base * Operator^(n) = Result[n]

**Example:**

*Recorrence:*
dp[i] = dp[i-1] + dp[i-2] + dp[i-3] + dp[i-4] + dp[i-5] + dp[i-6]

Base Matrix
[dp[5], dp[4], dp[3], dp[2], dp[1], dp[0]]

* Operator Matrix ^ 1
[1, 1, 0, 0, 0, 0]
[1, 0, 1, 0, 0, 0]
[1, 0, 0, 1, 0, 0]
[1, 0, 0, 0, 1, 0]
[1, 0, 0, 0, 0, 1]
[1, 0, 0, 0, 0, 0]

= Result Matrix
[dp[n+5], dp[n+4], dp[n+3], dp[n+2], dp[n+1], dp[n]]

```cpp
int32_t main(){ sws;
    ll n; cin >> n;
    Matrix op(6, 6, 1);
    op.M[0] = {1, 1, 0, 0, 0, 0};
    op.M[1] = {1, 0, 1, 0, 0, 0};
    op.M[2] = {1, 0, 0, 1, 0, 0};
    op.M[3] = {1, 0, 0, 0, 1, 0};
    op.M[4] = {1, 0, 0, 0, 0, 1};
    op.M[5] = {1, 0, 0, 0, 0, 0};

    Matrix base(vector(1, vll({16, 8, 4, 2, 1, 1})));
    if (n <= 5) cout << base.M[0][5-n] << endl; 
    else {
        op = op^(n-5);
        Matrix ans = base * op;
        cout << ans.M[0][0] << endl;
    }
}   
```