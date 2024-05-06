/**
 * Author: AlbertoTDNeto
 * Date: 14/04/2024
 * Description: Using Slope trick, compute the min cost to modify arry to be non-decreasing
 * Time: O(n \log{n})
 * Status: Tested
*/

// funcao f_i(x) = custo de deixar todo mundo ate i
// nao decrescente e <= x

// os pontos em changepoints sao os pontos da
// piecewise linear function convexa

// eu calculo g_i(x) = custo de deixar todo mundo ate i
// nao decrescente e v[i] == x

// entao f_i(x) = min(g_i(t) pra t <= x)

// podemos escrever gi(x) = fi-1(x) + |x-v[i]|
// entao a gente ta somando as funcoes e gerando outra convexa

// a resposta vai armazenar o custo (coord y) do opt
// e o topo do change_points vai ser o opt atual

// se opt < v[i] entao a gente calcula o g_i e o novo opt
// vai ser v[i]

// se opt > v[i] entao o slope entre opt e anterior opt vai ficar reto
// (este anterior opt podendo ser o v[i] que vai ser inserido),
// entao basta retirar o ultimo opt e teremos de novo a resposta
// neste caso devemos aumentar o custo do opt, que vai ser por
// (opt - v[i]) (so olhar a funcao em V do || e a convexa do fi-1)

// o v[i] vai ser inserido varias vezes no change_points
// pra denotar a inclinacao no slope dele

int32_t main() { sws;

    ll n; cin >> n;

    vector<ll> v(n);
    for(ll i = 0; i < n; i++) {
        cin >> v[i];
        // to change the problem 
        // from increasing to non-decreasing
        // v[i] -= i;
    }

    priority_queue<ll> change_points;
    change_points.push(-INF);
    ll ans = 0;

    for(ll i = 0; i < n; i++) {
        ll opt = change_points.top();
        change_points.push(v[i]);

        if(opt > v[i]) {
            ans += opt - v[i];
            change_points.push(v[i]);
            change_points.pop();
        }
    }

    cout << ans << endl;
}