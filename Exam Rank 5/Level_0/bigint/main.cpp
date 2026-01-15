#include "bigint.hpp"
#include <iostream>
#include <string>

void testAddition() {
    std::cout << "\nTesting Addition:\n";
    bigint num1("123456789012345678901234567890");
    bigint num2("987654321098765432109876543210");

    std::cout << "num1 + num2 = " << (num1 + num2) << "\n";

    // Caso límite
    bigint bigNum("999999999999999999999999999999");
    bigint smallNum("1");
    std::cout << "bigNum + smallNum = " << (bigNum + smallNum) << "\n";
}

void testIncrement() {
    std::cout << "\nTesting Increment:\n";
    bigint num("12345678901234567890");

    std::cout << "num++ = " << (num++) << ", num = " << num << "\n";
    std::cout << "++num = " << (++num) << "\n";
}

void testComparisons() {
    std::cout << "\nTesting Comparisons:\n";
    bigint a("1000");
    bigint b("2000");

    std::cout << "(a < b): " << (a < b) << ", "
              << "(b > a): " << (b > a) << "\n";

    // Caso límite: números grandes iguales
    bigint bigNum1("999999999999999999999999999999");
    bigint bigNum2(bigNum1);
    std::cout << "(bigNum1 == bigNum2): " << (bigNum1 == bigNum2) << "\n";
}

void testShifts() {
    std::cout << "\nTesting Shift Operations:\n";
    bigint num("1234");
	bigint bigNum1("10");

    // Left shift
    std::cout << "(num << 5) = " << (num << 5) << "\n";

    // Right shift
    std::cout << "(num >> 2) = " << (num >> 2) << "\n";
	bigint num2("12345678901");
	std::cout << "(num >>= bigNum1) = " << (num2 >>= bigNum1) << "\n";
}

void testEdgeCases() {
    std::cout << "\nTesting Edge Cases:\n";
    
    bigint zero("0");
    bigint negative("-12345678901234567890");

    // Zero addition
    std::cout << "zero + num = " << (zero + bigint("123")) << "\n";

    // Negative number test
    std::cout << "negative: " << negative << "\n";
}

int main() {
    testAddition();
    testIncrement();
    testComparisons();
    testShifts();
    testEdgeCases();

    return 0;
}