#ifndef INSTRUCTIONS_ASSERT_H
#define INSTRUCTIONS_ASSERT_H

#include <vector>

#include "Instruction.hpp"
#include "../Value.hpp"

class Assert: public Instruction {
public:
	Assert(std::vector<Value> const &);
	virtual ~Assert() { }

	void execute(AbstractStack<IOperand const *> &) const;

	enum class Wrong { type, value };

	class Exception: public Instruction::StdExcept {
	public:
		Exception(enum Wrong cause);
		virtual ~Exception() { }
		char const * what() const throw();
	private:
		enum Wrong cause;
	};

private:
	std::vector<Value> const args;
};

#endif // INSTRUCTIONS_ASSERT_H
