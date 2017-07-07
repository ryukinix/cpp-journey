// Manoel Cancer Plus Plus

#include <iostream>
#include <sstream>
#include <vector>

/*
  Input Format

  The first and only line consists of n integers separated by commas.

  Output Format

  Print the integers after parsing it.

  P.S.: I/O will be automatically handled. You need to complete the function only.

  Sample Input

  23,4,56
  Sample Output

  23
  4
  56
*/


std::vector<int> parseInts(std::string str) {
    std::stringstream ss(str);
    char c;
    int d;
    int numbers = str.size()/2;
    std::vector<int> v;
    ss >> d;
    v.push_back(d);
    while (!ss.eof()) { // check if is the end of string
        ss >> c >> d;
        v.push_back(d);

    }
    return v;
}



int main(int argc, char **argv) {
    std::string str;
    std::cin >> str;
    std::vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        std::cout << integers[i] << "\n";
    }

    return 0;
}
