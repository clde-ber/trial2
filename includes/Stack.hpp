#ifndef STACK_H
#define STACK_H

#include "Vector.hpp"

namespace ft
{
    template< typename T, class Container = vector< T > >
    class stack
    {
        private:
            size_t _n;
            size_t _capacity;
            T* _p;
        protected:
            Container _c;
        public:
            typedef Container container_type;
            typedef typename Container::value_type value_type;
            typedef typename Container::size_type size_type;
            typedef typename Container::reference reference;
            typedef typename Container::const_reference const_reference;

            friend bool ft::operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
            friend bool ft::operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
            friend bool ft::operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
            friend bool ft::operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
            friend bool ft::operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
            friend bool ft::operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);

            explicit stack(const Container& cont = Container()) : _n(0), _capacity(0), _p(0), _c(cont) {}
            stack(const stack& other) : _n(other._n), _capacity(other._capacity), _p(0), _c(other._c) {}
            stack& operator=(const stack& other)
            {
                _n = other._n;
                _capacity = other._capacity;
                _p = 0;
                _c = other._c;
                return *this;
            }
            virtual ~stack() {}
            size_type size() const
            {
                return _c.size();
            }
            bool empty() const
            {
                return _c.empty();
            }
            reference top()
            {
                return _c.back();
            }
            const_reference top() const
            {
                return _c.back();
            }
            void push(const value_type& value)
            {
                _c.push_back(value);
            }
            void pop()
            {
                _c.pop_back();
            }
    };

    template< class T, class Container >
    bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._c == rhs._c;
    }
    template< class T, class Container >
    bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._c != rhs._c;
    }
    template< class T, class Container >
    bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._c < rhs._c;
    }
    template< class T, class Container >
    bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._c <= rhs._c;
    }
    template< class T, class Container >
    bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._c > rhs._c;
    }
    template< class T, class Container >
    bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._c >= rhs._c;
    }
}

#endif