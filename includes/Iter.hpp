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
            virtual ~iter() {}
            iter& operator++() {_it = _it + 1; return *this;}
            iter operator++(int) {iter retval = *this; ++(*this); return retval;}
            iter& operator--() {_it = _it - 1; return *this;}
            iter operator--(int) {iter retval = *this; --(*this); return retval;}
            iter& operator-=(difference_type rhs) {_it = _it - rhs; return *this;}
            iter operator-(difference_type rhs) const {return iter(_it - rhs);}
            iter& operator+=(difference_type rhs) {_it = _it + rhs; return *this;}
            iter operator+(difference_type rhs) const {return iter(_it + rhs);}
            reference operator[](int rhs) {return *(_it + rhs);}
            T operator->() {return &operator*();}
            reference operator*() const {return *_it;}
            T base() const {return _it;}

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
            template < typename U >
            reviter(U const & rhs) : _it(&(*rhs)) {}
            template < typename U >
            reviter& operator=(U const & rhs) {_it = &(*rhs); return *this;}
            virtual ~reviter() {}
            reviter& operator++() {_it = _it - 1; return *this;}
            reviter operator++(int) {reviter retval = *this; ++(*this); return retval;}
            reviter& operator--() {_it = _it + 1; return *this;}
            reviter operator--(int) {reviter retval = *this; --(*this); return retval;}
            reviter& operator-=(difference_type rhs) {_it += rhs; return *this;}
            reviter operator-(difference_type rhs) const {return reviter(_it + rhs);}
            reviter& operator+=(difference_type rhs) {_it -= rhs; return *this;}
            reviter operator+(difference_type rhs) const {return reviter(_it - rhs);}
            reference operator[](int rhs) {return *(_it - rhs);}
            T operator->() {return &operator*();}
            reference operator*() const {reviter tmp(*this); return *(--tmp._it);}
            T base() const {return _it;}

            operator reviter<iter<const_iterator_type> >() {
                return (reviter<iter<const_iterator_type> >(iter<const_iterator_type>(_it)));
            }
    };
    template< typename T >
    std::ostream & operator<<(std::ostream & o, iter< T > const & rhs) {o << *rhs; return o;}
    template< typename T >
    std::ostream & operator<<(std::ostream & o, reviter< T > const & rhs) {o << *rhs; return o;}


    template< class Iterator1, class Iterator2 >
    std::ptrdiff_t operator-( const reviter<Iterator1>& lhs, const reviter<Iterator2>& rhs ) 
    {
        return lhs.base() - rhs.base();
    }
    template< class Iterator1, class Iterator2 >
    std::ptrdiff_t operator-( const iter<Iterator1>& lhs, const reviter<Iterator2>& rhs ) 
    {
        return lhs.base() - rhs.base();
    }
    template< class Iterator1, class Iterator2 >
    std::ptrdiff_t operator-( const reviter<Iterator1>& lhs, const iter<Iterator2>& rhs ) 
    {
        return lhs.base() - rhs.base();
    }
    template< class Iterator1, class Iterator2 >
    std::ptrdiff_t operator-( const iter<Iterator1>& lhs, const iter<Iterator2>& rhs ) 
    {
        return lhs.base() - rhs.base();
    }

    // friend vectorConstIterator operator+(difference_type n,
    //                                          const vectorConstIterator& rhs) {
    //         return vectorConstIterator(rhs._node + n);
    //     }

    template<class T>
	reviter<T>	operator+(std::ptrdiff_t n, reviter<T> const &it) { return (reviter<T>(n + &(*it))); }
    template<class T>
	reviter<T>	operator-(std::ptrdiff_t n, reviter<T> const &it) { return (reviter<T>(n - &(*it))); }
    template<class T>
	iter<T> operator+(std::ptrdiff_t n, iter<T> const &it) { return (iter<T>(n + &(*it))); }
    template<class T>
	iter<T> operator-(std::ptrdiff_t n, iter<T> const &it) { return (iter<T>(n - &(*it))); }

    template<typename T, typename U>
	bool			operator==(iter<T> const &lhs, iter<U> const &rhs) { return (&(*lhs) == &(*rhs)); }
    template<typename T, typename U>
    bool operator!=(iter<T> const &lhs, iter<U> const &rhs) {return !(&(*lhs) == &(*rhs));}
    template<typename T, typename U>
    bool operator>(iter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) > &(*rhs));}
    template<typename T, typename U>
    bool operator>=(iter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) >= &(*rhs));}
    template<typename T, typename U>
    bool operator<(iter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) < &(*rhs));}
    template<typename T, typename U>
    bool operator<=(iter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) <= &(*rhs));}

    template<typename T, typename U>
	bool			operator==(reviter<T> const &lhs, reviter<U> const &rhs) { return (&(*lhs) == &(*rhs)); }
    template<typename T, typename U>
    bool operator!=(reviter<T> const &lhs, reviter<U> const &rhs) {return !(&(*lhs) == &(*rhs));}
    template<typename T, typename U>
    bool operator>(reviter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) > &(*rhs));}
    template<typename T, typename U>
    bool operator>=(reviter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) >= &(*rhs));}
    template<typename T, typename U>
    bool operator<(reviter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) < &(*rhs));}
    template<typename T, typename U>
    bool operator<=(reviter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) <= &(*rhs));}

    template<typename T, typename U>
	bool			operator==(iter<T> const &lhs, reviter<U> const &rhs) { return (&(*lhs) == &(*rhs)); }
    template<typename T, typename U>
    bool operator!=(iter<T> const &lhs, reviter<U> const &rhs) {return !(&(*lhs) == &(*rhs));}
    template<typename T, typename U>
    bool operator>(iter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) > &(*rhs));}
    template<typename T, typename U>
    bool operator>=(iter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) >= &(*rhs));}
    template<typename T, typename U>
    bool operator<(iter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) < &(*rhs));}
    template<typename T, typename U>
    bool operator<=(iter<T> const &lhs, reviter<U> const &rhs) {return (&(*lhs) <= &(*rhs));}

    template<typename T, typename U>
	bool			operator==(reviter<T> const &lhs, iter<U> const &rhs) { return (&(*lhs) == &(*rhs)); }
    template<typename T, typename U>
    bool operator!=(reviter<T> const &lhs, iter<U> const &rhs) {return !(&(*lhs) == &(*rhs));}
    template<typename T, typename U>
    bool operator>(reviter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) > &(*rhs));}
    template<typename T, typename U>
    bool operator>=(reviter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) >= &(*rhs));}
    template<typename T, typename U>
    bool operator<(reviter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) < &(*rhs));}
    template<typename T, typename U>
    bool operator<=(reviter<T> const &lhs, iter<U> const &rhs) {return (&(*lhs) <= &(*rhs));}
}

#endif