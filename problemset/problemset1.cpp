#include <iostream>

int main() {
    long n;
    std::cin >> n;
    while (n!=1) {
        std::cout << n << " ";
        (n%2==0 ? n/=2 : n=n*3+1);
    }
    std::cout << 1;
}