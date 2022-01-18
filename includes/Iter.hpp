#ifndef ITER_H
#define ITER_H

#include <iostream>

namespace ft
{
    template< typename T >
    class iter
    {
        public:
            T* _it;
            iter() : _it(0) {}
            iter(T* x) : _it(x) {}
            iter(iter const & rhs) : _it(rhs._it) {}
            iter& operator=(iter const & rhs) {_it = rhs._it; return *this;}
            ~iter() {}
            iter& operator++() {_it = (_it + 1 >= _it) ? _it + 1: _it - 1; return *this;}
            iter operator++(int) {std::cout << "la" << std::endl; iter retval = *this; if (_it + 1 >= _it) ++(*this); else --(*this); return retval;}
            iter& operator--() {std::cout << "here" << std::endl;_it = (_it - 1 <= _it) ? _it - 1: _it + 1; return *this;}
            iter operator--(int) {std::cout << "there" << std::endl;iter retval = *this; if (_it - 1 <= _it) --(*this); else ++(*this); return retval;}
            bool operator==(const iter& rhs) const {return _it==rhs._it;}
            bool operator!=(const iter& rhs) const {return _it!=rhs._it;}
            iter operator-=(int const & rhs) {return (_it - rhs > _it) ? _it = _it + rhs : _it = _it - rhs;}
            iter operator-(int const & rhs) {return (_it - rhs > _it) ? _it = _it + rhs : _it = _it - rhs;}
            long operator-(iter const & rhs) const {return _it - rhs._it;}
            iter operator+=(int const & rhs) {return (_it - rhs < _it) ? _it = _it + rhs : _it = _it - rhs;}
            iter operator+(int const & rhs) {return (_it - rhs < _it) ? _it = _it + rhs : _it = _it - rhs;}
            long operator+(iter const & rhs) const {return _it + rhs._it;}
            T& operator[](int const rhs) {return *(_it + rhs);}
            iter& operator=(int const & rhs) {*_it = rhs; return *this;}
            T* operator->() {return _it;}
            T& operator*() {return *_it;}
            iter& base() {return *this;}
    };
    template< typename T >
    std::ostream & operator<<(std::ostream & o, iter< T > const & rhs) {std::cout << *rhs._it; return o;}
}

#endif