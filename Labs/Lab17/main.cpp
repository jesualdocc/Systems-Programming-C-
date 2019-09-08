#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdint>

int main() {
	std::vector<uint64_t> fib;

	fib.push_back(0);
	fib.push_back(1);
	fib.push_back(1);

	std::unordered_map<uint64_t, int> fibMap;
	fibMap[1] = 2;

	for (int i = 3; i < 94; i++) {

		uint64_t sum = fib[i - 1] + fib[i - 2];
		fib.push_back(sum);
		fibMap.insert(std::pair<uint64_t, int>(sum, i));
	}
	
	
	std::cout << "Fibonacci numbers in order:\n";
	std::vector<uint64_t>::iterator i;

	int j = 0;
	for (i = fib.begin(); i != fib.end(); ++i)
	{
		std::cout << j << " " << *i << std::endl;
		j++;
	}

	std::cout << "Fibonacci numbers and indices, unordered:\n";

	for (auto const& pair: fibMap) {
		std::cout << pair.second << " " << pair.first << std::endl;
	}

	std::cout << "Testing Fibonacci numbers from 1 to 15:\n";

	for (j = 1; j < 16; j++) {
		std::unordered_map<uint64_t, int>::const_iterator k = fibMap.find(j);
		if (k == fibMap.end()) {
			std::cout << j << " " << "no" << std::endl;
		}
		else {
			std::cout << j << " " << k->second << std::endl;
		}
	}

	return 0;
}