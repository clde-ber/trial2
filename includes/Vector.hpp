#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

#define MAX_SIZE 

namespace ft
{
    template< typename T >
    class vector
    {
        private:
            size_t _n;
            T* _p;
            size_t _capacity;
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

            vector( void ) : _n(0), _p(0), _capacity(0)
            {
                std::allocator< T > alloc;
                _p = alloc.allocate(_capacity, this);
            }
            vector( unsigned long n ) : _n(n), _p(0), _capacity(n)
            {
                std::allocator< T > alloc;
                _p = alloc.allocate(_capacity, this);
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
                _capacity = rhs._capacity;
                for (unsigned long i = 0; i < _capacity; i++)
                    _p[i] = rhs._p[i];
                return *this;
            }
            virtual ~vector( void )
            {
                std::allocator< T > alloc;
                alloc.deallocate(_p, _capacity);
                _capacity = 0;
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
                if (n < 0 or n >= _capacity)
                    throw OutOfLimitsException();
                return _p[n];
            }
            T & back()
            {
                if (!empty())
                    return _p[_n - 1];
                throw EmptyStackException();
            }
            T & front()
            {
                if (!empty())
                    return _p[0];
                throw EmptyStackException();
            }
            T * data()
            {
                if (!empty())
                    return &_p[0];
                throw EmptyStackException();
            }
            T & at(size_t pos)
            {
                if (!(pos < size()))
                    throw std::out_of_range("out of range");
                return _p[pos];
            }
            void push_back(T const & val)
            {
                vector< T > tmp(_capacity + 1);
                for (unsigned long i = 0; i < _capacity; i++)
                    tmp._p[i] = _p[i];
                tmp._p[_capacity] = val;
                this->~vector();
                *this = tmp;
            }
            void pop_back()
            {
                if (!_n)
                    throw EmptyStackException();
                std::allocator< T > alloc;
                vector< T > tmp(_capacity - 1);
                for (unsigned long i = 0; i < _capacity - 1; i++)
                    tmp._p[i] = _p[i];
                this->~vector();
                *this = tmp;
            }
            void reserve( size_t new_cap )
            {
                ft::vector< T > newV(new_cap);
                this->~vector();
                *this = newV;
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
