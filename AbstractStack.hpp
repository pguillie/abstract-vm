#ifndef ABSTRACTSTACK_H_
#define ABSTRACTSTACK_H_

#include <stack>

template<class T>
class AbstractStack : public std::stack<T> {
public:
	using std::stack<T>::c;	// the underlying container
				// (protected member object)
	auto begin() const { return c.begin(); }
	auto end() const { return c.end(); }
	auto rbegin() const { return c.rbegin(); }
	auto rend() const { return c.rend(); }
	auto cbegin() const { return c.cbegin(); }
	auto cend() const { return c.cend(); }
	auto crbegin() const { return c.crbegin(); }
	auto crend() const { return c.crend(); }
};

#endif // ABSTRACTSTACK_H_
