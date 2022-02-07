#ifndef MAP_H
#define MAP_H

#include "pair3.hpp"
#include "bidirectionalIt.hpp"
#include "EnableIf.hpp"
#include <stdexcept>
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <cmath>
#define TRUE 1
#define FALSE 0

namespace ft
{
    template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<Key, T> > >
    class map
    {
        class value_compare
            {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
                friend class map;
                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
                public:
                    typedef bool result_type;
                    typedef RBTree< Key, T, Compare, Allocator > first_argument_type;
                    typedef RBTree< Key, T, Compare, Allocator > second_argument_type;
                    bool operator() (const RBTree< Key, T, Compare, Allocator >& x, const RBTree< Key, T, Compare, Allocator >& y) const
                    {
                        return comp(x.first, y.first);
                    };
            };
        private:
            value_compare _value_compare;
            Compare _key_compare;
            RBTree<Key, T, Compare, Allocator > _p;
            size_t _n;
            size_t _capacity;
            Allocator _alloc;
        public:
            typedef Key key_type;
            typedef T mapped_type;
            typedef pair< Key, T > value_type;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef Compare key_compare;
            typedef Allocator allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef biIter< pointer > iterator;
            typedef biIter< const_pointer > const_iterator;
            typedef biReviter<iterator> reverse_iterator;
            typedef biReviter<const_iterator> const_reverse_iterator;
            explicit map(const Compare& comp = key_compare(), const Allocator& alloc = Allocator()) : _value_compare(comp), _key_compare(comp), _p(RBTree< Key, T, Compare, Allocator >()), _n(0), _capacity(0), _alloc(alloc)
            {
                pair< Key, T > *end = new pair< Key, T >(value_type(key_type(), mapped_type()));
                _p.setLast(end);
            }
            template< class InputIt >
            map(InputIt first, InputIt last, const Compare& comp = key_compare(), const Allocator& alloc = Allocator(), typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL) : _value_compare(comp), _key_compare(comp), _p(RBTree< Key, T, Compare, Allocator >()), _n(0), _capacity(0), _alloc(alloc)
            {
                pair< Key, T > *end = new pair< Key, T >(value_type(key_type(), mapped_type()));
                _p.setLast(end);
                insert(first, last);
            }
            map(const map& other)
            {
                *this = other;
            }
            ~map()
            {

            }
            map& operator=(const map& other)
            {
                _value_compare = value_compare();
                _key_compare = key_compare();
                _p = 0;
                _n = other._n;
                _capacity = other._capacity;
                _alloc = other._alloc;
                iterator it = other.begin();
                iterator ite = other.end();

                _p = RBTree< Key, T, Compare, Allocator >();
                pair< Key, T > *end = new pair< Key, T >(value_type(key_type(), mapped_type()));
                _p.setLast(end);
                insert(it, ite);
                return *this;
            }
            allocator_type get_allocator() const
            {

            }
            T& operator[](const Key& key)
            {
                return (*((insert(pair< Key, T >(key ,mapped_type()))).first)).second;
            }
            iterator begin()
            {
                if ((_p.getRoot()))
                    return iterator(_p.findMinimum(_p.getRoot()));
                return iterator(_p.getLast());
            }
            const_iterator begin() const
            {
                if ((_p.getRoot()))
                    return const_iterator(_p.findMinimum(_p.getRoot()));
                return const_iterator(_p.getLast());
            }
            iterator end()
            {
                return iterator(_p.getLast());
            }
            const_iterator end() const
            {
                return const_iterator(_p.getLast());
            }
            reverse_iterator rbegin()
            {
                return reverse_iterator(end());
            }
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end());
            }
            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }
            bool empty() const
            {
                if (!_n)
                    return TRUE;
                return FALSE;
            }
            size_type size() const
            {
                return _n;
            }
            size_type max_size() const
            {
                return (std::pow(2, 32) / sizeof(T) * std::pow(2, 32) - 1);
            }
            void clear()
            {
                erase(begin(), end());
            }
            pair<iterator, bool> insert(const value_type& value)
            {
                iterator it;
                int exists = 1;
				if ((it = iterator(_p.find(value))) == end())
                {
                    exists = 1;
					_p.insert(value);
                }
				return pair<iterator, bool>(iterator(_p.find(value)), exists);
            }
            iterator insert(iterator hint, const value_type& value)
            {
                (void)hint;
                if (iterator(_p.find(value)) == end())
                    _p.insert(value);
                return iterator(_p.find(value));
            }
            template< class InputIt >
            void insert(InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL)
            {
                while (first != last)
                {
                    if (iterator(_p.find(ft::pair< Key, T >(*first))) == end())
                        _p.insert(*first);
                    first++;
                }
            }
            void erase(iterator pos, typename ft::enable_if<!is_integral<iterator>::value>::type* = NULL)
            {
                iterator it = begin();
                iterator ite = end();

                if (!_p.getRoot())
                    return ;
                _p.deleteNode(pos->first);
                print();
            }
            void erase(iterator first, iterator last, typename ft::enable_if<!is_integral<iterator>::value>::type* = NULL)
            {
                /*if (!_p.getRoot())
                    return ;
                iterator tmp(first);
                while (first != last)
                {
                    tmp = first++;
                    std::cout << "first base " << (*first.base()).val << std::endl;
                    if (iterator(_p.find((*first.base()))) != end())
                        _p.deleteNode((*first.base()).val);
                    
                }*/
                iterator 	it = first;
				iterator	tmp;
				size_type	difference = 0;
				for (iterator ite = first; ite != last; ite++)
					difference++;

				for (size_type i = 0; i < difference; i++)
				{
					tmp = it;
					if (i != difference - 1)
						it++;
                    _p.deleteNode(tmp->first);
					if (i != difference - 1)
						it = iterator(_p.find(*it));
				}
				_n -= difference;
                print();
            }
            size_type erase(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();

                if (!_p.getRoot())
                    return 0;
                while (it != ite)
                {
                    if (it->first == key)
                    {
                        _p.deleteNode((*it.base()).first);
                        break ;
                    }
                    it++;
                }
                print();
                return 1;
            }
            void swap(map& x)
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
            size_type count(const Key& key) const
            {
                if (_p.find(key))
                    return TRUE;
                return FALSE;
            }
            iterator find(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();

                while (it != ite)
                {
                    if (it->first == key)
                        return _p.find(*it);
                    it++;
                }
                return end();
            }	
            const_iterator find(const Key& key) const
            {
                return _p.find(key);
            }
            RBTree< iterator,iterator, Compare, Allocator > equal_range(const Key& key)
            {
                return RBTree< Key, T, Compare, Allocator >(lower_bound(key), upper_bound(key));
            }
            RBTree< const_iterator,const_iterator, Compare, Allocator > equal_range(const Key& key) const
            {
                return RBTree< Key, T, Compare, Allocator >(lower_bound(key), upper_bound(key));
            }
            iterator lower_bound(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!comp(*it, key))
                        return it;
                    it++;
                }
            }
            const_iterator lower_bound(const Key& key) const
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!comp(*it, key))
                        return it;
                    it++;
                }
            }
            iterator upper_bound(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!comp(*it, key) && !equiv(*it, key))
                        return it;
                    it++;
                }
            }
            const_iterator upper_bound(const Key& key) const
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!comp(*it, key) && !equiv(*it, key))
                        return it;
                    it++;
                }
            }
            void print()
            {
                _p.prettyPrint();
            }
        //template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::RBTree<const Key, T> > >
    };

    template< class Key, class T, class Compare, class Alloc >
    bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);	
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
    template< class Key, class T, class Compare, class Alloc >
    bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
	template< class Key, class T, class Compare, class Alloc >
    bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
	template< class Key, class T, class Compare, class Alloc >
    bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
    template< class Key, class T, class Compare, class Alloc >
    bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);
}

#endif

/*
if (_it->parent && !_it->right)
                    {
                        _it = _it->parent;
                        return tmp;
                    }
                    if (_it->right && !_it->right->left)
                    {
                        std::cout << "lalala" << std::endl;
                        _it = _it->right;
                        return tmp;
                    }
                    if (_it->right && _it->right->left)
                    {
                        _it = _it->right;
                        while (_it->left)
                            _it = _it->left;
                        return tmp;
                    }
                    if (_it->right)
                    {
                        _it = _it->right;
                        return tmp;
                    }
                    if (_it->parent && _it->parent->second < _it->second)
                    {
                        while (_it->parent->second < tmp->second)
                            _it = _it->parent;
                        return tmp;
                    }
                    */