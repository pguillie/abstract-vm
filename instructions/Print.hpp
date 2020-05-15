#ifndef INSTRUCTIONS_PRINT_H
#define INSTRUCTIONS_PRINT_H

#include "Instruction.hpp"

class Print: public Instruction {
public:
	Print(int count = 1);
	virtual ~Print() { }

	void execute(AbstractStack<const IOperand*>&) const;

	class TypeException: public Instruction::StdExcept {
	public:
//		TypeException();
		virtual ~TypeException() { }
		const char* what() const throw();
	};

private:
	const int count;
};

#endif // INSTRUCTIONS_PRINT_H
