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
            typedef T iterator_type;
            typedef const value_type *			const_iterator_type;

            iter() : _it(T()) {}
            iter(iterator_type x) : _it(x) {}
            template< class U >
            iter(U const & other) : _it(&(*other)) {}
            template< class U >
            iter& operator=(U const & other) {_it = &(*other); return *this;}
            virtual ~iter() {}
            iter& operator++() {_it = _it + 1; return *this;}
            iter operator++(int) {iter retval = *this; ++(*this); return retval;}
            iter& operator--() {_it = _it - 1; return *this;}
            iter operator--(int) {iter retval = *this; --(*this); return retval;}
            iter& operator-=(difference_type n) {_it -= n; return *this;}
            iter operator-(difference_type n) const {return iter(_it - n);}
            iter& operator+=(difference_type n) {_it += n; return *this;}
            iter operator+(difference_type n) const {return iter(_it + n);}
            reference operator[](difference_type n) const {return *(_it + n);}
            pointer operator->() const {return &operator*();}
            reference operator*() const {return *_it;}
            iterator_type base() const {return _it;}

            operator const iter<const_iterator_type>() const
            {
                return (iter<const_iterator_type>(const_cast<const iterator_type>(_it)));
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
            typedef T iterator_type;
            typedef const value_type *			const_iterator_type;
            reviter() : _it(T()) {}
            reviter(iterator_type x) : _it(x) {}
            template< class U >
            reviter(U const & other) : _it(&(*other)) {}
            template< class U >
            reviter& operator=(U const & other) {_it = &(*other); return *this;}
            virtual ~reviter() {}
            reviter& operator++() {_it = _it - 1; return *this;}
            reviter operator++(int) {reviter retval = *this; ++(*this); return retval;}
            reviter& operator--() {_it = _it + 1; return *this;}
            reviter operator--(int) {reviter retval = *this; --(*this); return retval;}
            reviter& operator-=(difference_type n) {_it += n; return *this;}
            reviter operator-(difference_type n) const {return reviter(_it + n);}
            reviter& operator+=(difference_type n) {_it -= n; return *this;}
            reviter operator+(difference_type n) const {return reviter(_it - n);}
            reference operator[](difference_type n) const {return base()[-n-1];}
            pointer operator->() const {return &operator*();}
            reference operator*() const {reviter tmp(*this); return *(--tmp._it);}
            iterator_type base() const {return _it;}

            operator reviter<iter<const_iterator_type> >()
            {
                return (reviter<iter<const_iterator_type> >(iter<const_iterator_type>(_it)));
            }
    };
    template< typename T >
    std::ostream & operator<<(std::ostream & o, iter< T > const & rhs) {o << *rhs; return o;}
    template< typename T >
    std::ostream & operator<<(std::ostream & o, reviter< T > const & rhs) {o << *rhs; return o;}

    template< class Iter>
    iter<Iter> operator+( typename iter<Iter>::difference_type n, const iter<Iter>& it )
    {
        return iter<Iter>(it.base() + n);
    }
    template< class Iterator, class U >
    typename iter<Iterator>::difference_type operator-( const iter<Iterator>& lhs, const iter<U>& rhs )
    {
        return lhs.base() - rhs.base();
    }

    template< class Iter >
    reviter<Iter> operator+( typename reviter<Iter>::difference_type n, const reviter<Iter>& it )
    {
        return reviter<Iter>(it.base() - n);
    }
    template< class Iterator, class U >
    typename reviter<Iterator>::difference_type operator-( const reviter<Iterator>& lhs, const reviter<U>& rhs )
    {
        return rhs.base() - lhs.base();
    }

    template<typename Iterator1, typename Iterator2>
	bool			operator==(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator1, typename Iterator2>
    bool operator!=(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>=(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<=(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}

    template<typename Iterator1, typename Iterator2>
	bool			operator==(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator1, typename Iterator2>
    bool operator!=(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>=(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<=(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}
}

#endif