#ifndef BIDIRECTIONALITER_H
#define BIDIRECTIONALITER_H

#include <iostream>
#include "Iter.hpp"

namespace ft
{
    template< typename T >
    class biIter
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

            biIter() : _it(T()) {}
            biIter(iterator_type x) : _it(x) {}
            template< class U >
            biIter(U & other) : _it(&(*other)) {}
            template< class U >
            biIter& operator=(U & other) {_it = &(*other); return *this;}
            virtual ~biIter() {}
            biIter& operator++()
            {
                (*this)++;
                return *this;
            }
            biIter operator++(int)
            {
                T tmp = _it;
                
                if (_it && _it->right)
                {
                    _it = _it->right;
                    while (_it->left)
                        _it = _it->left;
                }
                else if (_it)
                {
                    // std::cout << "++" << std::endl;
                    while (_it->parent && _it == _it->parent->right)
                    {
                        // std::cout << "it parent right" << std::endl;
                        _it = _it->parent;
                    }
                    // if (_it->parent)
                    // std::cout << "it parent = " << _it->parent->first << std::endl;
                    _it = _it->parent;
                }
                return tmp;
            }
            biIter& operator--()
            {
                (*this)--;
                return *this;
            }
            biIter operator--(int)
            {
                T tmp = _it;
                if (_it && _it->left)
                    {
                        _it = _it->left;
                        while (_it->right)
                            _it = _it->right;
                    }
                else if (_it)
                {
                    while (_it->parent && _it == _it->parent->left)
                        _it = _it->parent;
                    if (_it->parent)
                        _it = _it->parent;
                }
                return tmp;
            }
            pointer operator->() const {return &operator*();}
            reference operator*() const {return *_it;}
            iterator_type base() const {return _it;}

            operator biIter<const_iterator_type>()
            {
                return (biIter<const_iterator_type>(const_cast<const iterator_type>(_it)));
            }
    };
    template< typename T >
    class biReviter
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
            biReviter() : _it(T()) {}
            biReviter(iterator_type x) : _it(x) {}
            template< class U >
            biReviter(U & other) : _it(other.base()) {}
            template< class U >
            biReviter& operator=(U & other) {_it = other.base(); return *this;}
            virtual ~biReviter() {}
            biReviter& operator--()
            {
                (*this)--;
                return *this;
            }
            biReviter operator--(int)
            {
                 T tmp = _it;
                
                if (_it && _it->right)
                {
                    _it = _it->right;
                    while (_it->left)
                        _it = _it->left;
                }
                else if (_it)
                {
                    while (_it->parent && _it == _it->parent->right)
                        _it = _it->parent;
                    _it = _it->parent;
                }
                return tmp;
            }
            biReviter& operator++()
            {
                (*this)++;
                return *this;
            }
            biReviter operator++(int)
            {
               T tmp = _it;
                if (_it && _it->left)
                    {
                        _it = _it->left;
                        while (_it->right)
                            _it = _it->right;
                    }
                else if (_it)
                {
                    while (_it->parent && _it == _it->parent->left)
                        _it = _it->parent;
                     _it = _it->parent;
                }
                return tmp;
            }
            pointer operator->() const {return &operator*();}
            reference operator*() const {T tmp(_it); return *--tmp;}
            iterator_type base() const {return _it;}

            operator biReviter<biIter<const_iterator_type> >()
            {
                return (biReviter<biIter<const_iterator_type> >(biIter<const_iterator_type>(_it)));
            }
    };

    template< class Iter>
    biIter<Iter> operator+( typename biIter<Iter>::difference_type n, const biIter<Iter>& it )
    {
        return biIter<Iter>(it.base() + n);
    }
    template< class Iterator, class U >
    typename biIter<Iterator>::difference_type operator-( const biIter<Iterator>& lhs, const biIter<U>& rhs )
    {
        return lhs.base() - rhs.base();
    }

    template< class Iter >
    biReviter<Iter> operator+( typename biReviter<Iter>::difference_type n, const biReviter<Iter>& it )
    {
        return biReviter<Iter>(it.base() - n);
    }
    template< class Iterator, class U >
    typename biReviter<Iterator>::difference_type operator-( const biReviter<Iterator>& lhs, const biReviter<U>& rhs )
    {
        return rhs.base() - lhs.base();
    }

    template<typename Iterator1, typename Iterator2>
	bool			operator==(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator1, typename Iterator2>
    bool operator!=(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>=(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<=(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}

    template<typename Iterator1, typename Iterator2>
	bool			operator==(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator1, typename Iterator2>
    bool operator!=(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>=(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<=(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}
}

#endif