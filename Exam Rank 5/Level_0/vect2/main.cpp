#include "practice.hpp"        // incluye la definición de la clase vect2
#include <iostream>			// incluye la biblioteca de entrada/salida para mostrar resultados

int main() 
{
	vect2 v1;				// 0, 0
	vect2 v2(1, 2);			// 1, 2
	const vect2 v3(v2);		// 1, 2
	vect2 v4 = v2;			// 1, 2

	std::cout << "v1: " << v1 << std::endl;	// 0, 0
	std::cout << "v1: " << "{" << v1[0] << "," << v1[1] << "}" << std::endl;	// 0, 1
	std::cout << "v2: " << v2 << std::endl;	// 1, 2
	std::cout << "v3: " << v3 << std::endl;	// 1, 2
	std::cout << "v4: " << v4 << std::endl;	// 1, 2
	std::cout << v4++ << std::endl; 		// 2, 3
	std::cout << ++v4 << std::endl; 		// 3, 4
	std::cout << v4-- << std::endl; 		// 2, 3
	std::cout << --v4 << std::endl; 		// 1, 2
	std::cout << (v2 += v3) << std::endl; 								// 2, 4
	std::cout << (v1 -= v2) << std::endl; 								// -2, -4
	std::cout << (v2 = v3 + v3 * 2) << std::endl; 						// 3, 6
	std::cout << (v2 = 3 * v2) << std::endl; 							// 9, 18
	std::cout << (v2 += v2 += v3) << std::endl; 						// 20, 40
	std::cout << (v1 *= 42) << std::endl; 								// -84, -168
	std::cout << "Suma 0: " << (v1 = v1 - v1 + v1) << std::endl;						// 0, 0
	std::cout << "v1: " << v1 << std::endl;			// 0, 0
	std::cout << "v2: " << v2 << std::endl;			// 20, 40
	std::cout << "-v2: " << -v2 << std::endl;		// -20, -40
	std::cout << "v1[1]: " << v1[1] << std::endl;	// 0
	v1[1] = 12;
	std::cout << "v1[1]: " << v1[1] << std::endl;	// 12
	std::cout << "v3[1]: " << v3[1] << std::endl;	// 2
	std::cout << "v1 == v3: " << (v1 == v3) << std::endl;	// 0
	std::cout << "v1 == v1: " << (v1 == v1) << std::endl;	// 1
	std::cout << "v1 != v3: " << (v1 != v3) << std::endl;	// 1
	std::cout << "v1 != v1: " << (v1 != v1) << std::endl;	// 0 */
}
