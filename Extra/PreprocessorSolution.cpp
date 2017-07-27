/* Enter your macros here */
#include <climits>
//#define INF ((1 << 31) - 1) // THIS OVERFLOW, how get max int with bitwise?
#define INF INT_MAX
#define FUNCTION(name, comp) void name(int &a, int b){ a = a comp b? a : b;}
#define io(v) cin >> v
#define foreach(v, i) for(unsigned int i = 0; i < v.size(); i++)
#define toStr(s) #s


#include <iostream>
#include <vector>
using namespace std;

#if !defined toStr || !defined io || !defined FUNCTION || !defined INF
#error Missing preprocessor definitions
#endif

FUNCTION(minimum, <)
FUNCTION(maximum, >)

int main(){
    int n; cin >> n;
    vector<int> v(n);
    foreach(v, i) {
        io(v)[i];
    }
    int mn = INF;
    int mx = -INF;
    foreach(v, i) {
        minimum(mn, v[i]);
        maximum(mx, v[i]);
    }
    int ans = mx - mn;
    cout << toStr(Result =) <<' '<< ans;
    return 0;

}
