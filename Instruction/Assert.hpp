#ifndef INSTRUCTION_ASSERT_H
#define INSTRUCTION_ASSERT_H

#include <vector>

#include "Instruction.hpp"
#include "Value.hpp"

class Assert: public Instruction {
public:
	Assert(void) =delete;
	Assert(const Assert& o) =delete;
	Assert(Assert&& o) =delete;
	Assert(const std::vector<Value>& args);
	virtual ~Assert(void);
	Assert& operator=(const Assert& o) =delete;
	Assert& operator=(Assert&& o) =delete;

	void execute(AbstractStack<const IOperand*>& stack) const;

	enum class Wrong {
		type, value
	};

	class Exception: public Instruction::StdExcept {
	public:
		Exception(void) =delete;
		Exception(const Exception& o) =delete;
		Exception(Exception&& o) =delete;
		Exception(enum Wrong cause);
		virtual ~Exception(void);
		Exception& operator=(const Exception& o) =delete;
		Exception& operator=(Exception&& o) =delete;

		const char* what(void) const throw();

	private:
		enum Wrong cause;
	};

private:
	const std::vector<Value> args;
};

#endif // INSTRUCTION_ASSERT_H
