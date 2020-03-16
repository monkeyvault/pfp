#include <iostream>

int main() {
	int n;
	int m = 1000000007;
	long r = 1;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		r*=2;
		if (r>m) r%=m;
	}
	std::cout << r;
}