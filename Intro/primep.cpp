#include <iostream>
#include <cmath>
#include <cstdlib>

bool isprime(int n) q{
    for (int i = 2; i <= std::sqrt(n) + 1; i++) {
        if (n % i == 0) {
            return false;
            break;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Usage: primep [number]" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    if (isprime(n)) {
        std::cout << "Is prime" << std::endl;
    } else {
        std::cout << "Is not prime" << std::endl;
    }

    return 0;
}
