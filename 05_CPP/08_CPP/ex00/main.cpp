#include "easyfind.hpp"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

using std::cerr; using std::cout; using std::endl;

int	main() {

	// Values to initialize vector
	int	ini = 33; int end = 128;

	std::vector<int> vec;

	cout << BLUE << "\nVector: { ";

	for (int i = ini; i <= end; i++) {
		vec.push_back(i);
		cout << i << (i < end ? ", " : " }");
	}

	cout << RESET << endl;

	int j;

	cout << "\nSelect number to find in vector 🕵️‍♂️ : ";
	while (!(std::cin >> j)) {
		if (std::cin.eof()) {
			cout << "\n🔒 EOF signal (Ctrl+D) detected.\n";
			return 1;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//
		cout << RED << "~Invalid input 🤬 " << RESET << "try to do better : ";
	}

	cout << endl;

	try {
		if (easyfind(vec, j))
			cout << GREEN << "Perfect! " << RESET << "Value " << j << " found in vector 👌" << endl;
	}	catch (const std::exception &e) {
		cerr << RED << e.what() << RESET << endl;
		return (1);
	}

	return 0;

}