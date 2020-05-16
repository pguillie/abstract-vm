#ifndef INSTRUCTION_PRINT_H
#define INSTRUCTION_PRINT_H

#include "Instruction.hpp"

class Print: public Instruction {
public:
	Print(void);
	Print(const Print& o) =delete;
	Print(Print&& o) =delete;
	Print(int count);
	virtual ~Print(void);
	Print& operator=(const Print& o) =delete;
	Print& operator=(Print&& o) =delete;

	void execute(AbstractStack<const IOperand*>& stack) const;

	class TypeException: public Instruction::StdExcept {
	public:
		TypeException(void);
		TypeException(const TypeException& o) =delete;
		TypeException(TypeException&& o) =delete;
		virtual ~TypeException(void);
		TypeException& operator=(const TypeException& o) =delete;
		TypeException& operator=(TypeException&& o) =delete;

		const char* what(void) const throw();
	};

private:
	const int count;
};

#endif // INSTRUCTION_PRINT_H
