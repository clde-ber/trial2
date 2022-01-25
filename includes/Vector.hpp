#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <cmath>
#include "Iter.hpp"

#define TRUE 1
#define FALSE 0

namespace ft
{
    // template< typename T, class It = iter< T > >
    template <typename T, T val>
	struct storage
	{
		static const T value = val;
	};

	struct false_type : public storage<bool, false> {};
	struct true_type : public storage<bool, true> {};

	template <class T> struct is_integral : public false_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<short> : public true_type {};
	template <> struct is_integral<unsigned short> : public true_type {};
	template <> struct is_integral<long> : public true_type {};
	template <> struct is_integral<unsigned long> : public true_type {};
	template <> struct is_integral<long long> : public true_type {};
	template <> struct is_integral<unsigned long long> : public true_type {};

	template<bool B, typename T = void>
		struct enable_if {};

	template<typename T>
		struct enable_if<true, T> { typedef T type; };

    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        private:
            size_t _n;
            T* _p;
            size_t _capacity;
        public:
            typedef size_t size_type;
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef iter<pointer> iterator;
            typedef reviter< iterator > reverse_iterator;
            typedef iter< const_pointer > const_iterator;
            typedef reviter< const_iterator > const_reverse_iterator;

            explicit vector (const allocator_type& alloc = allocator_type()) : _n(0), _p(0), _capacity(0)
            {
                Alloc allocator = alloc;
                _p = allocator.allocate(1);
            }
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _n(n), _p(0), _capacity(n)
            {
                Alloc allocator = alloc;
                _p = allocator.allocate(_capacity);
                for (size_type i = 0; i < _capacity; i++)
                    allocator.construct(&_p[i], val);
            }
            vector( const vector & x ) : _n(x._n), _p(0), _capacity(x._capacity)
            {
                *this = x;
            }
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value>::type* = NULL) : _n(0), _p(0), _capacity(0)
            {
                Alloc allocator = alloc;
                size_type i = 0;
                while (first != last)
                {
                    i++;
                    first++;
                }
                _n = i;
                _capacity = i;
                _p = allocator.allocate(_capacity);
                while (i)
                {
                    first--;
                    i--;
                }
                while (i < _capacity)
                    allocator.construct(&_p[i++], *first++);
                while (i)
                {
                    first--;
                    i--;
                }
                //assign(first, last);
            }
            vector & operator=( vector const & x )
            {
                Alloc allocator;
                _n = x._n;
                _capacity = x._capacity;
                _p = allocator.allocate(_capacity);
                for (size_type i = 0; i < _capacity; i++)
                    allocator.construct(&_p[i], x._p[i]);
                return *this;
            }
            virtual ~vector( void )
            {
                if (_p)
                {
                    std::allocator< T > alloc;
                    for (size_type i = 0; i < _capacity; i++)
                        alloc.destroy(&_p[i]);
                    alloc.deallocate(_p, _capacity);
                    _capacity = 0;
                    _n = 0;
                    _p = 0;
                }
            }
            iterator begin()
            {
                iterator ret(_p);
                return ret;
            }
            const_iterator begin() const
            {
                const_iterator ret(_p);
                return ret;
            }
            iterator end()
            {
                iterator ret(_p + _n);
                return ret;
            }
            const_iterator end() const
            {
                const_iterator ret(_p + _n);
                return ret;
            }
            reverse_iterator rbegin()
            {
                reverse_iterator ret(end());
                return ret;
            }
            const_reverse_iterator rbegin() const
            {
                const_reverse_iterator ret(end());
                return ret;
            }
            reverse_iterator rend()
            {
                reverse_iterator ret(begin());
                return ret;
            }
            const_reverse_iterator rend() const
            {
                const_reverse_iterator ret(begin());
                return ret;
            }
            size_type size() const
            {
                return _n;
            }
            bool empty() const
            {
                if (!_n)
                    return TRUE;
                return FALSE;
            }
            reference operator[] (size_type n)
            {
                return _p[n];
            }
            const_reference operator[] (size_type n) const
            {
                return _p[n];
            }
            T* data()
            {
                return _p;
            }
            const T* data () const
            {
                return _p;
            }
            reference back()
            {
                if (!empty())
                    return _p[_n - 1];
                throw std::exception();
            }
            const_reference back() const
            {
                if (!empty())
                    return _p[_n - 1];
                throw std::exception();
            }
            reference front()
            {
                if (!empty())
                    return _p[0];
                throw std::exception();
            }
            const_reference front() const
            {
                if (!empty())
                    return _p[0];
                throw std::exception();
            }
            reference at(size_t n)
            {
                if (!(n < size()))
                    throw std::out_of_range("");
                return _p[n];
            }
            const_reference at(size_t n) const
            {
                if (!(n < size()))
                    throw std::out_of_range("");
                return _p[n];
            }
            void reserve( size_type n )
            {
                size_type len = size();
                if (n > _capacity)
                {
                    resize(n);
                    _n = len;
                    //ft::vector< T > newV(n);
                    //this->~vector();
                    //*this = newV;
                    //newV.~vector();
                }
            }
            void resize (size_type n, value_type val = value_type())
            {
                ft::vector< T > tmp2(n);
                unsigned long i = 0;
                while (i < n && i < size())
                {
                    tmp2._p[i] = _p[i];
                    i++;
                }
                while (i < n)
                    tmp2._p[i++] = val;
                *this = tmp2;
                tmp2.~vector();
            }
            void push_back (const value_type& val)
            {
                resize(_capacity + 1, val);
            }
            void pop_back()
            {
                if (!_n)
                    throw std::exception();
               resize(_capacity - 1);
            }
            size_type capacity() const
            {
                return _capacity;
            }
            size_type max_size() const
            {
                return (std::pow(2, 32) / sizeof(T) * std::pow(2, 32)) - 1;
            }
            template <class InputIterator>
            void assign(InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value>::type* = NULL)
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
            void assign(size_type n, const value_type& val)
            {
                insert(begin(), n, val);
                resize(n);
            }
            void insert(iterator position, size_type n, const value_type& val)
            {
                size_type i = 0;
                size_type x = 0;
                size_type len = _capacity;
                while (position != begin())
                {
                    position--;
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
                //this->~vector();
                *this = res;
                //copy.~vector();
                //res.~vector();
            }
            template <class InputIterator>
            void insert(iterator pos, InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value>::type* = NULL)
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
                //this->~vector();
                *this = res;
                //copy.~vector();
                //res.~vector();
            }
            iterator insert (iterator position, const value_type& val)
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
                //this->~vector();
                *this = res;
                //copy.~vector();
                //res.~vector();
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
            void swap(vector& x)
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
                //this->~vector();
                vector< T > tmp;
                *this = tmp;
            }
    };
    template< class T, class Alloc >
    bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return lhs.size() == rhs.size();
    }
    template< class T, class Alloc >
    bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }
    template< class T, class Alloc >
    bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template< class T, class Alloc >
    bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)      
    {
        return !(rhs < lhs);
    } 
    template< class T, class Alloc >
    bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return rhs < lhs;
    }
    template< class T, class Alloc >
    bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif
