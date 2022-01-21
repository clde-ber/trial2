#ifndef ITER_H
#define ITER_H

#include <iostream>

namespace ft
{
    struct input_interator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag {};
    struct bidirectional_iterator_tag {};
    struct random_access_iterator_tag {};

    template < class Iter >
    struct iterator_traits {
        typedef typename Iter::difference_type		difference_type;
        typedef typename Iter::value_type			value_type;
        typedef typename Iter::pointer				pointer;
        typedef typename Iter::reference			reference;
        typedef typename Iter::iterator_category	iterator_category;
    };

    template < class T >
    struct iterator_traits<T*> {
        typedef std::ptrdiff_t					difference_type;
        typedef T								value_type;
        typedef T *								pointer;
        typedef T &								reference;
        typedef random_access_iterator_tag	iterator_category;
    };

    template < class T >
    struct iterator_traits<T* const> {
        typedef std::ptrdiff_t					difference_type;
        typedef T								value_type;
        typedef const T *						pointer;
        typedef const T &						reference;
        typedef random_access_iterator_tag	iterator_category;
    };

    template< typename T >
    class iter
    {
        private:
            T _it;
        public:
            typedef typename iterator_traits<T>::value_type			value_type;
            typedef typename iterator_traits<T>::difference_type	difference_type;
            typedef typename iterator_traits<T>::pointer			pointer;
            typedef typename iterator_traits<T>::reference			reference;
            typedef typename iterator_traits<T>::iterator_category	iterator_category;
            iter() : _it(T()) {}
            iter(T x) : _it(x) {}
            template < typename U >
            iter(U const & rhs) : _it(&(*rhs)) {}
            template < typename U >
            iter& operator=(U const & rhs) {_it = &(*rhs); return *this;}
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
            reference operator[](int rhs) {return *(_it + rhs);}
            int operator=(int const rhs) {return rhs;}
            pointer operator->() {return _it;}
            reference operator*() const {return *_it;}
            T base() {return *_it;}

            operator const iter<const value_type *>() const {
                return (iter<const value_type *>(const_cast<const T>(_it)));
            }
    };
    template< typename T >
    class reviter
    {
        private:
            T _it;
        public:
            typedef	typename iterator_traits<T>::difference_type		difference_type;
            typedef	typename iterator_traits<T>::value_type			value_type;
            typedef	typename iterator_traits<T>::pointer				pointer;
            typedef	typename iterator_traits<T>::reference			reference;
            typedef	typename iterator_traits<T>::iterator_category	iterator_category;
            typedef const value_type *			const_iterator_type;

            reviter() : _it(T()) {}
            reviter(T x) : _it(x) {}
            //reviter(reviter const & rhs) {_it = rhs._it;}
            template < typename U >
            reviter(U const & rhs) : _it(&(*rhs)) {}
            template < typename U >
            reviter& operator=(U const & rhs) {_it = &(*rhs); return *this;}
            virtual ~reviter() {}
            reviter& operator++() {--_it; return *this;}
            reviter operator++(int) {reviter retval = *this; --_it; return retval;}
            reviter& operator--() {++_it; return *this;}
            reviter operator--(int) {reviter retval = *this; ++_it; return retval;}
            reviter& operator-=(int rhs) {while (rhs) { _it++; rhs--;} return *this;}
            reviter operator-(int rhs) {reviter tmp = *this; while (rhs) { tmp._it++; rhs--;}return tmp;}
            reviter& operator+=(int rhs) {while (rhs) { _it--; rhs--;} return *this;}
            reviter operator+(int rhs) const {reviter tmp = *this; while (rhs) { tmp._it--; rhs--;}return tmp;}
            reference operator[](int rhs) {return base()[-rhs-1];}
            T operator->() {return &operator*();}
            reference operator*() const {T tmp = _it; return *--tmp;}
            T base() {return _it;}

            operator reviter<iter<const_iterator_type> >() {
                return (reviter<iter<const_iterator_type> >(iter<const_iterator_type>(_it)));
            }
    };
    template< typename T >
    std::ostream & operator<<(std::ostream & o, iter< T > const & rhs) {o << *rhs; return o;}
    template< typename T >
    std::ostream & operator<<(std::ostream & o, reviter< T > const & rhs) {o << *rhs; return o;}


    template<class T>
	iter<T>	operator+(int n, iter<T> &it) { return (n + &(*it)); }
    template<class T>
	iter<T>	operator-(int n, iter<T> &it) { return (n - &(*it)); }
    template<class T>
	reviter< T > operator+(int n, reviter< T > &it) { return (n + &(*it)); }
    template<class T>
	reviter< T > operator-(int n, reviter< T > &it) { return (n - &(*it)); }

    template<class T, class U>
	long operator+(iter<T> &it, iter<U> &it2) { return (&(*it) + &(*it2)); }
    template<class T, class U>
	long	operator-(iter<T> &it, iter<U> &it2) { return (&(*it) - &(*it2)); }
    template<class T, class U>
	long operator+(reviter<T> &it, reviter< U > &it2) { return (&(*it) + &(*it2)); }
    template<class T, class U>
	long operator-(reviter<T> &it, reviter< U > &it2) { return (&(*it) - &(*it2)); }

     template<class T, class U>
	long operator+(reviter<T> &it, iter<U> &it2) { return (&(*it) + &(*it2)); }
    template<class T, class U>
	long	operator-(reviter<T> &it, iter<U> &it2) { return (&(*it) - &(*it2)); }
    template<class T, class U>
	long operator+(iter<T> &it, reviter< U > &it2) { return (&(*it) + &(*it2)); }
    template<class T, class U>
	long operator-(iter<T> &it, reviter< U > &it2) { return (&(*it) - &(*it2)); }

    template<class T, class U>
	bool			operator==(iter<T> const &lhs, iter<U> const &rhs) { return (&(*lhs) == &(*rhs)); }
    template<class T, class U>
    bool operator!=(iter<T> const &lhs, iter<U> const &rhs) {return !(&(*lhs) == &(*rhs));}
    template<class T, class U>
    bool operator>(iter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) > &(*rhs));}
    template<class T, class U>
    bool operator>=(iter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) >= &(*rhs));}
    template<class T, class U>
    bool operator<(iter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) < &(*rhs));}
    template<class T, class U>
    bool operator<=(iter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) <= &(*rhs));}

    template<class T, class U>
	bool			operator==(reviter< T > const &lhs, reviter< U > const &rhs) { return (&(*lhs) == &(*rhs)); }
    template<class T, class U>
    bool operator!=(reviter< T > const &lhs, reviter< U > const &rhs) {return !(&(*lhs) == &(*rhs));}
    template<class T, class U>
    bool operator>(reviter< T > const &lhs, reviter< U > const &rhs) {return (&(*lhs) > &(*rhs));}
    template<class T, class U>
    bool operator>=(reviter< T > const &lhs, reviter< U > const &rhs) {return (&(*lhs) >= &(*rhs));}
    template<class T, class U>
    bool operator<(reviter< T > const &lhs, reviter< U > const &rhs) {return (&(*lhs) < &(*rhs));}
    template<class T, class U>
    bool operator<=(reviter< T > const &lhs, reviter< U > const &rhs) {return (&(*lhs) <= &(*rhs));}

    template<class T, class U>
	bool			operator==(iter<T> const &lhs, reviter<U> const &rhs) { return (&(*lhs) == &(*rhs)); }
    template<class T, class U>
    bool operator!=(iter<T> const &lhs, reviter<U> const &rhs) {return !(&(*lhs) == &(*rhs));}
    template<class T, class U>
    bool operator>(iter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) > &(*rhs));}
    template<class T, class U>
    bool operator>=(iter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) >= &(*rhs));}
    template<class T, class U>
    bool operator<(iter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) < &(*rhs));}
    template<class T, class U>
    bool operator<=(iter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) <= &(*rhs));}

    template<class T, class U>
	bool			operator==(reviter< T > const &lhs, iter< U > const &rhs) { return (&(*lhs) == &(*rhs)); }
    template<class T, class U>
    bool operator!=(reviter< T > const &lhs, iter< U > const &rhs) {return !(&(*lhs) == &(*rhs));}
    template<class T, class U>
    bool operator>(reviter< T > const &lhs, iter< U > const &rhs) {return (&(*lhs) > &(*rhs));}
    template<class T, class U>
    bool operator>=(reviter< T > const &lhs, iter< U > const &rhs) {return (&(*lhs) >= &(*rhs));}
    template<class T, class U>
    bool operator<(reviter< T > const &lhs, iter< U > const &rhs) {return (&(*lhs) < &(*rhs));}
    template<class T, class U>
    bool operator<=(reviter< T > const &lhs, iter< U > const &rhs) {return (&(*lhs) <= &(*rhs));}
}

#endif