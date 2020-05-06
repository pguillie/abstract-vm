#ifndef ABSTRACTSTACK_H_
#define ABSTRACTSTACK_H_

#include <deque>
#include <stack>

template<class T>
class AbstractStack : public std::stack<T, std::deque<T>> {
public:
	using std::stack<T>::c;	// the underlying container
				// (protected member object)

	typedef typename std::deque<T>::iterator iterator;
	typedef typename std::deque<T>::reverse_iterator reverse_iterator;
	typedef typename std::deque<T>::const_iterator const_iterator;
	typedef typename std::deque<T>::const_reverse_iterator const_reverse_iterator;

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
