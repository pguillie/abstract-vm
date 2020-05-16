#ifndef INSTRUCTIONS_EXIT_H_
#define INSTRUCTIONS_EXIT_H_

#include "Instruction.hpp"

class Exit: public Instruction {
public:
	Exit(void);
	Exit(const Exit& o) =delete;
	Exit(Exit&& o) =delete;
	virtual ~Exit(void);
	Exit& operator=(const Exit& o) =delete;
	Exit& operator=(Exit&& o) =delete;

	void execute(AbstractStack<const IOperand*>& stack) const;

	static void clean(AbstractStack<const IOperand*>& stack);

	class Exception: public std::exception {
	public:
		Exception(void);
		Exception(const Exception& o) =delete;
		Exception(Exception&& o) =delete;
		virtual ~Exception(void);
		Exception& operator=(const Exception& o) =delete;
		Exception& operator=(Exception&& o) =delete;

		const char* what(void) const throw();
	};
};

#endif // INSTRUCTIONS_EXIT_H_
