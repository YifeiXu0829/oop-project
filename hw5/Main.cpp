#include <iostream>
using namespace std;

#include "Printer.h"

int main() {
	std::cout << "Printer is warming up...please be patient!" << std::endl;

	Printer * p = new Printer();

	cout << "All I want to do is print...so all I'm doing is printing...\n";
	p->print();

	return 0;
}
