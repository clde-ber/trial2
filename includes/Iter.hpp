#ifndef ITER_H
#define ITER_H

#include <iostream>

namespace ft
{
    template< typename T >
    class iter
    {
        private:
            T* _it;
        public:
            iter() : _it(0) {}
            iter(T* x) : _it(x) {}
            iter(iter const & rhs) : _it(rhs._it) {}
            template < typename U >
            iter(U const & rhs) {_it = &(*rhs);}
            iter& operator=(iter const & rhs) {_it = rhs._it; return *this;}
            ~iter() {}
            iter& operator++() {_it = _it + 1; return *this;}
            iter operator++(int) {iter retval = *this; ++(*this); return retval;}
            iter& operator--() {_it = _it - 1; return *this;}
            iter operator--(int) {iter retval = *this; --(*this); return retval;}
            // bool operator==(const iter& rhs) const {return _it==rhs._it;}
            // bool operator>(const iter& rhs) const {return _it>rhs._it;}
            // bool operator>=(const iter& rhs) const {return _it>=rhs._it;}
            // bool operator<(const iter& rhs) const {return _it<rhs._it;}
            // bool operator<=(const iter& rhs) const {return _it<=rhs._it;}
            iter operator-=(int const & rhs) {return _it = _it - rhs;}
            iter operator-(int const & rhs) {return _it - rhs;}
            long operator-(iter const & rhs) const {return _it - rhs._it;}
            iter operator+=(int const & rhs) {return _it = _it + rhs;}
            iter operator+(int const & rhs) const {return _it + rhs;}
            T& operator[](int const rhs) {return *(_it + rhs);}
            int operator=(int const rhs) {return rhs;}
            T* operator->() {return _it;}
            T& operator*() const {return *_it;}
            iter& base() {return *this;}

            operator iter<const T>() const {
                return (iter<const T>(_it));
            }
    };
    template< typename T >
    class reviter
    {
        private:
            T* _it;
        public:
            reviter() : _it(0) {}
            reviter(T* x) : _it(x) {}
            reviter(reviter const & rhs) : _it(rhs._it) {}
            template < typename U >
            reviter(U const & rhs) {_it = &(*rhs);}
            reviter& operator=(reviter const & rhs) {_it = rhs._it; return *this;}
            ~reviter() {}
            reviter& operator++() {_it = _it - 1; return *this;}
            reviter operator++(int) {reviter retval = *this; --(*this); return retval;}
            reviter& operator--() {_it = _it + 1; return *this;}
            reviter operator--(int) {reviter retval = *this; ++(*this); return retval;}
            // bool operator==(const reviter& rhs) const {return _it==rhs._it;}
            // bool operator>(const reviter& rhs) const {return _it>rhs._it;}
            // bool operator>=(const reviter& rhs) const {return _it>=rhs._it;}
            // bool operator<(const reviter& rhs) const {return _it<rhs._it;}
            // bool operator<=(const reviter& rhs) const {return _it<=rhs._it;}
            reviter operator-=(int const & rhs) {return _it = _it + rhs;}
            reviter operator-(int const & rhs) {return _it + rhs;}
            reviter operator+=(int const & rhs) {return _it = _it - rhs;}
            reviter operator+(int const & rhs) const {return _it - rhs;}
            T& operator[](int const rhs) {return *(_it - rhs);}
            int operator=(int const rhs) {return rhs;}
            T* operator->() {return _it;}
            T& operator*() const {return *_it;}
            reviter& base() {return *this;}

            operator reviter<const T>() const {
                return (reviter<const T>(_it));
            }
    };
    template< typename T >
    std::ostream & operator<<(std::ostream & o, iter< T > const & rhs) {std::cout << *rhs; return o;}
    template< typename T >
    std::ostream & operator<<(std::ostream & o, reviter< T > const & rhs) {std::cout << *rhs; return o;}


    template<class T>
	iter<T>	operator+(int n, iter<T> &it) { return (n + &(*it)); }
    template<class T>
	iter<T>	operator-(int n, iter<T> &it) { return (n - &(*it)); }
    template<class T>
	reviter< T > operator+(int n, reviter< T > &it) { return (n + &(*it)); }
    template<class T>
	reviter< T > operator-(int n, reviter< T > &it) { return (n - &(*it)); }



    template<class T, class U>
	bool			operator==(iter<T> const &lhs, iter<U> const &rhs) { return (&(*lhs) == &(*rhs)); }
    template<class T, class U>
    bool operator!=(iter<T> const &lhs, iter<U> const &rhs) {return !(&(*lhs) == &(*rhs));}
    template<class T, class U>
    bool operator>(iter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) > &(*rhs));}
    template<class T, class U>
    bool operator>=(iter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) >= &(*rhs));}
    template<class T, class U>
    bool operator<(iter<T> const &lhs, iter<U> const &rhs) {return !(&(*lhs) >= &(*rhs));}
    template<class T, class U>
    bool operator<=(iter<T> const &lhs, iter<U> const &rhs) {return !(&(*lhs) > &(*rhs));}

    template<class T, class U>
	bool			operator==(reviter< T > const &lhs, reviter< U > const &rhs) { return (&(*lhs) == &(*rhs)); }
    template<class T, class U>
    bool operator!=(reviter< T > const &lhs, reviter< U > const &rhs) {return !(&(*lhs) == &(*rhs));}
    template<class T, class U>
    bool operator>(reviter< T > const &lhs, reviter< U > const &rhs) {return (&(*lhs) > &(*rhs));}
    template<class T, class U>
    bool operator>=(reviter< T > const &lhs, reviter< U > const &rhs) {return (&(*lhs) >= &(*rhs));}
    template<class T, class U>
    bool operator<(reviter< T > const &lhs, reviter< U > const &rhs) {return !(&(*lhs) >= &(*rhs));}
    template<class T, class U>
    bool operator<=(reviter< T > const &lhs, reviter< U > const &rhs) {return !(&(*lhs) > &(*rhs));}
}
#endif