/**
 * Author: Wallace, Bruno Monteiro
 * Date: 04/05/2024
 * Description: Matrix structure using vector<vector<T>> as a container.
 * Time: O(n^2) for sum, O(n^3) for product and O(n^3 log(k)) for fexp
 * Status: Tested (https://cses.fi/problemset/result/9170259/)
*/

template<class T> struct Matrix : vector<vector<T>> {
    ll n, m; // rows, columns

    // identity == 0 => Empty matrix constructor
    // identity == 1 => Generates a Identity Matrix (square matrix)
    Matrix(ll row, ll col, bool identity = 0) : n(row), m(col) {
        (*this).assign(row, vector<T>(col, 0));
        if (identity) {
            assert(n == m);
            for(ll i=0; i<n; i++) (*this)[i][i] = 1;
        }
    }

    // A+B (sizeof(A) == sizeof(B))
    Matrix operator +(const Matrix &b) const { // O(n^2)
        assert(n == b.n and m == b.m);
        Matrix ans(n, m);
        for(ll i=0; i<n; i++){
            for(ll j=0; j<m; j++){
                ans[i][j] = (*this)[i][j] + b[i][j];
            }
        }
        return ans;
    }

    // A*B (A.column == B.row)  
    Matrix operator *(const Matrix &b) const { // O(n^3)
        ll n2 = b.n, m2 = b.m;
        assert(m == n2);
        Matrix ans(n, m2);
        for(ll i=0; i<n; i++){
            for(ll j=0; j<m2; j++){
                for(ll k=0; k<n2; k++){
                    ans[i][j] += (*this)[i][k] * b[k][j];
                }
            }
        }
        return ans;
    }

    // A^i (n == m)
    Matrix operator ^(ll i) const{ // O(n^3 log(i))
        assert(n == m);
        Matrix ans(n, n, 1); // identity matrix
        Matrix tmp = *this;
        while(i) {
            if (i & 1) ans = (ans * tmp);
            tmp = (tmp * tmp);
            i >>= 1;
        }
        return ans;
    }
};