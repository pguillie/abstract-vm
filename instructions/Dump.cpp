#include "Dump.hpp"

Dump::Dump(int count):
	count(count < 0 ? 0 : count)
{ }

void Dump::execute(AbstractStack<const IOperand*> & stack) const
{
	int c = count;
	int size;

	if (verbose) {
		cout << "[+] dump";
		if (c)
			cout << " (" << c << " value" << (c > 1 ? "s" : "")
			     << ")";
		cout << std::endl;
		size = stack.size();
		if (size == 0)
			cout << "... empty stack\n";
		else if (size < c)
			cout << "... stack contains only " << size << " value"
			     << (size > 1 ? "s" : "") << ":\n";
	}
	for (auto it = stack.crbegin() ; it != stack.crend() && (!count || c) ;
	     it++, c--) {
		if (verbose) {
			switch ((*it)->getType()) {
			case (INT8): cout << "int8\t"; break;
			case (INT16): cout << "int16\t"; break;
			case (INT32): cout << "int32\t"; break;
			case (FLOAT): cout << "float\t"; break;
			case (DOUBLE): cout << "double\t"; break;
			}
		}
		cout << (*it)->toString() << std::endl;
	}
}
