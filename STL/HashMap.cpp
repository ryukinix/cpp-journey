#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

// 1 -> add
// 2 -> erase
// 3 -> find

int main(void) {
     int n; std::cin >> n;
     std::map<std::string, int> m;
     while(n--) {
          int command; std::cin >> command;
          std::string student; std::cin >> student;
          if (command == 1) {
               int mark; std::cin >> mark;
               if (m.find(student) != m.end()) {
                    m[student] += mark;
               } else {
                    m[student] = mark;
               }
          } else if (command == 2) {
               m.erase(student);

          } else if (command == 3) {
               if (m.find(student) != m.end()) {
                    std::cout << m[student];
               } else {
                    std::cout << 0;
               }

               std::cout << std::endl;

          }
     }
}
