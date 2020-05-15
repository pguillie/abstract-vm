#ifndef INSTRUCTIONS_ASSERT_H
#define INSTRUCTIONS_ASSERT_H

#include <vector>

#include "Instruction.hpp"
#include "../Value.hpp"

class Assert: public Instruction {
public:
	Assert(const std::vector<Value>&);
	virtual ~Assert() { }

	void execute(AbstractStack<const IOperand*> &) const;

	enum class Wrong { type, value };

	class Exception: public Instruction::StdExcept {
	public:
		Exception(enum Wrong cause);
		virtual ~Exception() { }

		const char* what() const throw();

	private:
		enum Wrong cause;
	};

private:
	const std::vector<Value> args;
};

#endif // INSTRUCTIONS_ASSERT_H
