#include <bits/stdc++.h>
using namespace std;

// Constants
const int INF = 1e9 + 7;          // A large value, useful for initialization
const long long LINF = 1e18 + 7;  // A large value for long long types
const double EPS = 1e-9;          // A small value for floating-point comparisons
const int MOD = 1e9 + 7;          // Modulo value for modular arithmetic

// Macros
#define fastio                   \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define rrep(i, a, b) for (int i = a; i > b; --i)
#define sz(x) (int)(x).size()
#define debug(x) cerr << #x << " = " << (x) << endl;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;

// Utility functions
template <typename T>
void print_vector(const vector<T>& v) {
    for (const auto& x : v) cout << x << ' ';
    cout << endl;
}

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll mod_exp(ll base, ll exp, ll mod = MOD) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    fastio;

    // Example usage
    int n;
    cin >> n;
    vi arr(n);
    rep(i, 0, n) {
        cin >> arr[i];
    }

    sort(all(arr));

    cout << "Sorted array: ";
    print_vector(arr);

    return 0;
}