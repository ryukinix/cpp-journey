/* Copyright <c> 2017 Manoel Vilela & HackerRank */
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
     vector<long> v;
     int n; cin >> n;

     // reading the vector
     for (int i = 0; i < n; i++) {
          long x; cin >> x;
          v.push_back(x);
     }

     int q; cin >> q;
     for (int i = 0; i < q; i++) {
          long x; cin >> x;
          vector<long>::iterator low = lower_bound(v.begin(), v.end(), x);
          int index = low - v.begin();
          if (v[index] == x) {
               cout << "Yes ";
          } else {
               cout << "No ";
          }
          cout << index + 1 << endl;

     }
     return 0;
}
