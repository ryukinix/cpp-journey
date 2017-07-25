#include <iostream>
#include <iomanip>

using namespace std;


void print_hex(long long A){
    cout << setw(0) << nouppercase // remove uppercase flag
         << showbase // show base
         << setbase(16) // use hex base
         << A // integral A
         << endl;

}

void print_fixed_filled(double B) {
    // right fill with _
    cout << right << setfill('_')
         << setw(0xf) << fixed  // define width to 15 and fixed notation
         << setprecision(2) << showpos // show sign and setprecision to 2
         << B << endl;
}

void print_scientific(double C) {
    // use uppercase, noshowpos (sign +/-)
    // set scientific mode for floating-number and set precision to 9
    cout << uppercase << noshowpos
         << scientific << setprecision(9)
         << C << endl;
}

int main() {
    int T; cin >> T;
    cout << setiosflags(ios::uppercase);
    cout << setw(0xf) << internal;
    while(T--) {
        double A; cin >> A;
        double B; cin >> B;
        double C; cin >> C;
        print_hex(A);
        print_fixed_filled(B);
        print_scientific(C);
    }
    return 0;

}
