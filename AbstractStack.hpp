#ifndef ABSTRACTSTACK_H_
#define ABSTRACTSTACK_H_

#include <deque>
#include <stack>

template<class T>
class AbstractStack: public std::stack<T, std::deque<T>> {
public:
	using std::stack<T>::c;	// the underlying container
				// (protected member object)

	typedef typename std::deque<T>::iterator
	iterator;

	typedef typename std::deque<T>::reverse_iterator
	reverse_iterator;

	typedef typename std::deque<T>::const_iterator
	const_iterator;

	typedef typename std::deque<T>::const_reverse_iterator
	const_reverse_iterator;

	auto begin(void) const;
	auto end(void) const;
	auto rbegin(void) const;
	auto rend(void) const;
	auto cbegin(void) const;
	auto cend(void) const;
	auto crbegin(void) const;
	auto crend(void) const;
};

template<class T>
auto AbstractStack<T>::begin(void) const
{
	return c.begin();
}

template<class T>
auto AbstractStack<T>::end(void) const
{
	return c.end();
}

template<class T>
auto AbstractStack<T>::rbegin(void) const
{
	return c.rbegin();
}

template<class T>
auto AbstractStack<T>::rend(void) const
{
	return c.rend();
}

template<class T>
auto AbstractStack<T>::cbegin(void) const
{
	return c.cbegin();
}

template<class T>
auto AbstractStack<T>::cend(void) const
{
	return c.cend();
}

template<class T>
auto AbstractStack<T>::crbegin(void) const
{
	return c.crbegin();
}

template<class T>
auto AbstractStack<T>::crend(void) const
{
	return c.crend();
}

#endif // ABSTRACTSTACK_H_
