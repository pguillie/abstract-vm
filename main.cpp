#include <iostream>

#include "Operand.hpp"
#include "avm.hpp"

int main(int argc, char * argv[]) {
	std::queue<Instruction *> instr;

	if (argc > 2) {
		std::cerr << "Usage: " << argv[0] << " [file]\n";
		return 1;
	}
	instr = parse(argv[1] ? argv[1] : "");
	while (!instr.empty())
	{
		Instruction * i = instr.front();
		std::cout << i->name << ":";
		for (auto it = i->args.begin() ; it != i->args.end(); ++it)
			std::cout << it->back() << "(" << it->front() << "),";
		std::cout << std::endl;
		instr.pop();
	}

			/////////////////////

	Operand<float> a(41);
	Operand<int16_t> b(88);
	Operand<int> c(123456789);
	Operand<float> d(3.14);
	Operand<double> e(1234567890.0987654321);

	std::cout << "precision: " << d.toString() << "\n";

	const IOperand * p;

	p = d + Operand<int>(0);
	std::cout << p->toString() << " (type: " << p->getType() << ")" << std::endl;
	p = b % a;
	std::cout << p->toString() << " (type: " << p->getType() << ")" << std::endl;
	p = a / d;
	std::cout << p->toString() << " (type: " << p->getType() << ")" << std::endl;
	p = e * a;
	std::cout << p->toString() << " (type: " << p->getType() << ")" << std::endl;

	std::cout << 10 * 3.14 << "\n" << std::to_string(3.14) << "\n";

	return 0;
}
