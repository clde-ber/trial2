#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>

#define MAX_SIZE 

namespace ft
{
    template< typename T >
    class vector
    {
        private:
            unsigned long _n;
            T* _p;
        class OutOfLimitsException : public std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return "Vector element exception: out of limits!";
                }
        };
        class EmptyStackException : public std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return "Vector exception: empty vector!";
                }
        };
        public:
            typedef T* iterator;
            typedef T* reverse_iterator;

            vector( void ) : _n(0), _p(0)
            {
                std::allocator< T > alloc;
                _p = alloc.allocate(_n, this);
            }
            vector( unsigned long n ) : _n(n), _p(0)
            {
                std::allocator< T > alloc;
                _p = alloc.allocate(_n, this);
            }
            vector( const vector & rhs )
            {
                *this = rhs;
            }
            vector & operator=( vector const & rhs )
            {
                std::allocator< T > alloc;
                _p = alloc.allocate(rhs._n, this);
                _n = rhs._n;
                for (unsigned long i = 0; i < _n; i++)
                    _p[i] = rhs._p[i];
                return *this;
            }
            virtual ~vector( void )
            {
                std::allocator< T > alloc;
                alloc.deallocate(_p, _n);
                _n = 0;
                _p = 0;
            }
            unsigned long size() const
            {
                return _n;
            }
            iterator begin()
            {
                return &_p[0];
            }
            iterator end()
            {
                return &_p[_n];
            }
            iterator rbegin()
            {
                return &_p[_n];
            }
            iterator rend()
            {
                return &_p[0];
            }
            bool empty() const
            {
                if (!_n)
                    return TRUE;
                return FALSE;
            }
            T & operator[](unsigned long n)
            {
                if (n < 0 or n >= _n)
                    throw OutOfLimitsException();
                return _p[n];
            }
    };
};

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
