#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>
#include <cstddef>
#include <algorithm>
#include "Iter.hpp"

#define TRUE 1
#define FALSE 0

namespace ft
{
    // template< typename T, class It = iter< T > >
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        private:
            size_t _n;
            T* _p;
            size_t _capacity;
        public:
            typedef int size_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef iter<T> iterator;
            typedef reviter< T > reverse_iterator;
            typedef iter< const T > const_iterator;
            typedef reviter< const T > const_reverse_iterator;

            vector( void ) : _n(0), _p(0), _capacity(0)
            {
                //std::allocator< T > alloc;
                //_p = alloc.allocate(_capacity, this);
            }
            vector( unsigned long n ) : _n(n), _p(0), _capacity(n)
            {
                std::allocator< T > alloc;
                _p = alloc.allocate(_capacity, this);
            }
            vector( unsigned long n, T const & value ) : _n(n), _p(0), _capacity(n)
            {
                std::allocator< T > alloc;
                _p = alloc.allocate(_capacity, this);
                for (unsigned long i = 0; i < _capacity; i++)
                    _p[i] = value;
            }
            vector( const vector & rhs ) : _n(rhs._n), _p(0), _capacity(rhs._capacity)
            {
                *this = rhs;
            }
            template< typename U >
            vector(U it, U ite) : _n(0), _p(0), _capacity(0)
            {
                assign(it, ite);
            }
            vector & operator=( vector const & rhs )
            {
                _p = 0;
                _n = rhs._n;
                _capacity = rhs._capacity;
                std::allocator< T > alloc;
                _p = alloc.allocate(rhs._capacity, this);
                for (unsigned long i = 0; i < rhs._capacity; i++)
                    _p[i] = rhs._p[i];
                return *this;
            }
            virtual ~vector( void )
            {
               /*if (_p)
                {
                    std::allocator< T > alloc;
                    alloc.deallocate(_p, _capacity);
                    _capacity = 0;
                    _n = 0;
                    _p = 0;
                }*/
            }
            iterator begin()
            {
                iterator ret(&_p[0]);
                return ret;
            }
            iterator end()
            {
                iterator ret(&_p[_n]);
                return ret;
            }
            reverse_iterator rbegin()
            {
                reverse_iterator ret(&_p[_n - 1]);
                return ret;
            }
            reverse_iterator rend()
            {
                reverse_iterator ret(&_p[0] - 1);
                return ret;
            }
            const_iterator begin() const
            {
                const_iterator ret(&_p[0]);
                return ret;
            }
            const_iterator end() const
            {
                return (const_iterator(&_p[_n]));
            }
            const_reverse_iterator rbegin() const
            {
                const_reverse_iterator ret(&_p[_n - 1]);
                return ret;
            }
            const_reverse_iterator rend() const
            {
                const_reverse_iterator ret(&_p[0] - 1);
                return ret;
            }
            bool operator==(const ft::vector< T >& rhs) const {return this->_p==rhs._p;}
            bool operator!=(const ft::vector< T >& rhs) const {return this->_p!=rhs._p;}
            bool operator>(const ft::vector< T >& rhs) const {return this->_p>rhs._p;}
            bool operator>=(const ft::vector< T >& rhs) const {return this->_p>=rhs._p;}
            bool operator<(const ft::vector< T >& rhs) const {return this->_p<rhs._p;}
            bool operator<=(const ft::vector< T >& rhs) const {return this->_p<=rhs._p;}
            unsigned long size() const
            {
                return _n;
            }
            bool empty() const
            {
                if (!_n)
                    return TRUE;
                return FALSE;
            }
            T & operator[](unsigned long n)
            {
                if (n < 0 or n >= _capacity)
                    throw std::exception();
                return _p[n];
            }
            T & back() const
            {
                if (!empty())
                    return _p[_n - 1];
                throw std::exception();
            }
            T & front() const
            {
                if (!empty())
                    return _p[0];
                throw std::exception();
            }
            T * data()
            {
                if (!empty())
                    return &_p[0];
                throw std::exception();
            }
            T & at(size_t pos) const
            {
                if (!(pos < size()))
                    throw std::out_of_range("");
                return _p[pos];
            }
            void reserve( size_t new_cap )
            {
                ft::vector< T > newV(new_cap);
                this->~vector();
                *this = newV;
                newV.~vector();
            }
            void resize (size_t n, T const & value = value_type())
            {
                ft::vector< T > tmp2(n);
                unsigned long i = 0;
                while (i < n && i < size())
                {
                    tmp2._p[i] = _p[i];
                    i++;
                }
                while (i < n)
                    tmp2._p[i++] = value;
                *this = tmp2;
                tmp2.~vector();
            }
            void push_back(T const & val)
            {
                resize(_capacity + 1, val);
            }
            void pop_back()
            {
                if (!_n)
                    throw std::exception();
               resize(_capacity - 1);
            }
            size_t capacity() const
            {
                return _capacity;
            }
            size_t ft_pow(size_t n, size_t pow) const
            {
                size_t i = 0;
                size_t res = 1;

                while (i < pow)
                {
                    res = res * n;
                    i++;
                }
                return res;
            }
            size_t max_size() const
            {
                return (ft_pow(2, 32) / sizeof(T)) * ft_pow(2, 32) - 1;
            }
            template< typename U >
            void assign(U first, U last)
            {
               size_t i = 0;
               size_t len = 0;
                while(first != last)
                {
                    first++;
                    i++;
                }
                len = i;
                while (i--)
                    first--;
                insert(begin(), first, last);
                resize(len);
            }
            void assign(size_type n, T const & value)
            {
                insert(begin(), n, value);
                resize(n);
            }
            void insert(iterator pos, size_type const n, const T & val)
            {
                size_type i = 0;
                size_type x = 0;
                size_type len = _capacity;
                while (pos != begin())
                {
                    pos--;
                    i++;
                }
                ft::vector< T > copy(*this);
                ft::vector< T > res(_n + n);
                for (x = 0; x < i; x++)
                    res._p[x] = copy._p[x];
                for (size_type y = 0; y < n; y++)
                    res._p[x++] = val;
                while (i < len)
                    res._p[x++] = copy._p[i++];
                this->~vector();
                *this = res;
                copy.~vector();
                res.~vector();
            }
            template< typename U >
            void insert(iterator pos, U first, U last)
            {
                size_type i = 0;
                size_type ct = 0;
                size_type x = 0;
                size_type y = 0;
                size_type len = size();
                while (pos != begin())
                {
                    pos--;
                    i++;
                }
                while (first != last)
                {
                    ct++;
                    first++;
                    y++;
                }
                while (y--)
                    first--;
                ft::vector< T > copy(*this);
                ft::vector< T > res(_n + ct);
                for (x = 0; x < i; x++)
                    res._p[x] = copy._p[x];
                for (size_type y = 0; y < ct; y++)
                    res._p[x++] = *(first++);
                while (i < len)
                    res._p[x++] = copy._p[i++];
                this->~vector();
                *this = res;
                copy.~vector();
                res.~vector();
            }
            iterator insert (iterator position, const T & val)
            {
                size_type i = 0;
                size_type x = 0;
                size_type len = _capacity;
                unsigned long pos = 0;
                while (position != begin())
                {
                    position--;
                    i++;
                    pos++;
                }
                ft::vector< T > copy(*this);
                ft::vector< T > res(_n + 1);
                for (x = 0; x < i; x++)
                    res._p[x] = copy._p[x];
                res._p[x++] = val;
                while (i < len)
                    res._p[x++] = copy._p[i++];
                this->~vector();
                *this = res;
                copy.~vector();
                res.~vector();
                return begin() + pos;
            }
            iterator erase(iterator position)
            {
                unsigned long i = 0;
                unsigned long pos = 0;
                iterator it = begin();
                iterator ite = end();
                while (it != position && it != ite)
                {
                    i++;
                    it++;
                }
                pos = i;
                it++;
                while (it != ite)
                {
                    _p[i] = _p[i + 1];
                    i++;
                    it++;
                }
                resize(i);
                return begin() + pos;
            }
            iterator erase(iterator first, iterator last)
            {
                unsigned long i = 0;
                unsigned long len = 0;
                unsigned long pos = 0;
                iterator it = begin();
                iterator ite = end();
                while (it != first && it != ite)
                {
                    it++;
                    i++;
                }
                pos = i;
                while (it != last && it != ite)
                {
                    len++;
                    it++;
                }
                while (it != ite)
                {
                    _p[i] = _p[i + len];
                    i++;
                    it++;
                }
                resize(i);
                return begin() + pos;
            }
            void swap(ft::vector< T > & x)
            {
                T *tmpP = x._p;
                size_t tmpC = x._capacity;
                size_t tmpN = x._n;
                x._p = this->_p;
                x._capacity = this->_capacity;
                x._n = this->_n;
                this->_p = tmpP;
                this->_capacity = tmpC;
                this->_n = tmpN;
            }
            void clear()
            {
                this->~vector();
                vector< T > tmp;
                *this = tmp;
            }
    };
}
// this x
// a    b

// tmp = this
// this = x
// x = tmp
#endif
/*
begin
    Return iterator to beginning (public member function )

end
    Return iterator to end (public member function )

rbegin
    Return reverse iterator to reverse beginning (public member function )

rend
    Return reverse iterator to reverse end (public member function )

size
    Return size (public member function ) OK

max_size
    Return maximum size (public member function )

resize
    Change size (public member function )

capacity
    Return size of allocated storage capacity (public member function )

empty
    Test whether vector is empty (public member function ) OK

reserve
    Request a change in capacity (public member function )

operator[]
    Access element (public member function )

at
    Access element (public member function )

front
    Access first element (public member function )

back
    Access last element (public member function )

assign
    Assign vector content (public member function )

push_back
    Add element at the end (public member function )

pop_back
    Delete last element (public member function )

insert
    Insert elements (public member function )

erase
    Erase elements (public member function )

swap
    Swap content (public member function )

clear
    Clear content (public member function )

get_allocator
    Get allocator (public member function )

*/
