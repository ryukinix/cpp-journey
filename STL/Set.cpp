#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

// 1 -> Add
// 2 -> Delete
// 3 -> Find :: Yes | No

int main() {
     int n; cin >> n;
     set<int> s;
     while(n--) {
          int x; cin >> x;
          int y; cin >> y;
          if (x == 1) {
               s.insert(y);
          } else if (x == 2) {
               // can be called to remove non-existent elements
               s.erase(y);
          } else if (x == 3) {
               if (s.find(y) != s.end()) {
                    cout << "Yes" << endl;
               } else {
                    cout << "No" << endl;
               }
          }
     }

     return 0;
}
