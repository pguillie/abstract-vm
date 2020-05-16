#ifndef INSTRUCTIONS_PUSH_H_
#define INSTRUCTIONS_PUSH_H_

#include <vector>

#include "Instruction.hpp"
#include "../OperandFactory.hpp"
#include "../Value.hpp"

class Push: public Instruction {
public:
	Push(void) =delete;
	Push(const Push& o) =delete;
	Push(Push&& o) =delete;
	Push(const std::vector<Value>&);
	virtual ~Push(void);
	Push& operator=(const Push& o) =delete;
	Push& operator=(Push&& o) =delete;

	void execute(AbstractStack<const IOperand*>& stack) const;

private:
	const std::vector<Value> args;
	static const OperandFactory factory;
};

#endif // INSTRUCTIONS_PUSH_H_
