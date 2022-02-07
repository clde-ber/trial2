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
                    bool operator() (const pair< Key, T >& x, const pair< Key, T >& y) const
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
            explicit map(const Compare& comp = key_compare(), const Allocator& alloc = Allocator()) : _value_compare(comp), _key_compare(comp), _p(RBTree< Key, T, Compare, Allocator >(comp)), _n(0), _capacity(0), _alloc(alloc)
            {
                pair< Key, T > *end = new pair< Key, T >(value_type(key_type(), mapped_type()));
                _p.setLast(end);
            }
            template< class InputIt >
            map(InputIt first, InputIt last, const Compare& comp = key_compare(), const Allocator& alloc = Allocator(), typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL) : _value_compare(comp), _key_compare(comp), _p(RBTree< Key, T, Compare, Allocator >(comp)), _n(0), _capacity(0), _alloc(alloc)
            {
                pair< Key, T > *end = new pair< Key, T >(value_type(key_type(), mapped_type()));
                _p.setLast(end);
                insert(first, last);
            }
            map(const map& other) : _value_compare(other._value_compare), _key_compare(other._key_compare), _p(RBTree< Key, T, Compare, Allocator >(other._key_compare)), _n(other._n), _capacity(other._capacity), _alloc(other._alloc)
            {
                pair< Key, T > *end = new pair< Key, T >(value_type(key_type(), mapped_type()));
                _p.setLast(end);
                insert(other.begin(), other.end());
            }
            ~map()
            {

            }
            map& operator=(const map& other)
            {
                _value_compare = other._value_compare;
                _key_compare = other._key_compare;
                _n = other._n;
                _capacity = other._capacity;
                _alloc = other._alloc;

                _p = RBTree< Key, T, Compare, Allocator >(_key_compare);
                pair< Key, T > *end = new pair< Key, T >(value_type(key_type(), mapped_type()));
                _p.setLast(end);
                insert(other.begin(), other.end());
                return *this;
            }
            key_compare key_comp() const
            {
                return _key_compare;
            }
            value_compare value_comp() const
            {
                return _value_compare;
            }
            allocator_type get_allocator() const
            {
                return allocator_type();
            }
            T& operator[](const Key& key)
            {
                if (find(key) == end())
					_n++;
                return (*((insert(pair< Key, T >(key ,mapped_type()))).first)).second;
            }
            iterator begin()
            {
                if (_p.getRoot())
                    return iterator(_p.findMinimum(_p.getRoot()));
                return iterator(_p.getLast());
            }
            const_iterator begin() const
            {
                if (_p.getRoot())
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
                _p.freeNodes(_p.getRoot());
                _n = 0;
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
            }
            void erase(iterator first, iterator last, typename ft::enable_if<!is_integral<iterator>::value>::type* = NULL)
            {
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
            }
            size_type erase(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();

                if (!_p.getRoot())
                    return 0;
                if (find(key) != end())
                {
                    erase(find(key));
                    return 1;
                }
                return 0;
            }
            void swap(map& x)
            {
                RBTree< Key, T, Compare, Allocator > tmpP = x._p;
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
                if (find(key) != end())
                    return TRUE;
                return FALSE;
            }
            iterator find(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();

                std::cout << "init find map (" << key << ")" << std::endl;
                _p.prettyPrint();
                while (it != ite)
                {
                    if (it->first == key)
                        return _p.find(*it);
                    // std::cout << "it = " << it->first << std::endl;
                    it++;
                }
                std::cout << "end find map (" << key << ")" << std::endl;
                return it;
            }	
            const_iterator find(const Key& key) const
            {
                const_iterator it = begin();
                const_iterator ite = end();

                while (it != ite)
                {
                    if (it->first == key)
                        return _p.find(*it);
                    it++;
                }
                return const_iterator(it);
            }
            pair< iterator,iterator > equal_range(const Key& key)
            {
                return value_type().make_pair(lower_bound(key), upper_bound(key));
            }
            pair< const_iterator,const_iterator > equal_range(const Key& key) const
            {
                return value_type().make_pair(lower_bound(key), upper_bound(key));
            }
            iterator lower_bound(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!_key_compare(it->first, key))
                        return it;
                    it++;
                }
                return it;
            }
            const_iterator lower_bound(const Key& key) const
            {
                const_iterator it = begin();
                const_iterator ite = end();
                while (it != ite)
                {
                    if (!_key_compare(it->first, key))
                        return it;
                    it++;
                }
                return it;
            }
            iterator upper_bound(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!_key_compare(it->first, key))
                        return it;
                    it++;
                }
                return it;
            }
            const_iterator upper_bound(const Key& key) const
            {
                const_iterator it = begin();
                const_iterator ite = end();
                while (it != ite)
                {
                    if (!_key_compare(it->first, key))
                        return it;
                    it++;
                }
                return it;
            }
            void print()
            {
                _p.prettyPrint();
            }
        //template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::RBTree<const Key, T> > >
    };

    template< class Key, class T, class Compare, class Alloc >
    bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        for (typename ft::map<Key,T,Compare,Alloc>::const_iterator it = lhs.begin(), it2 = rhs.begin(); it != lhs.end(); it++, it2++)
		{
            if (*it != *it2)
				return lhs.size() == rhs.size();;
        }
        return FALSE;
    }	
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
	template< class Key, class T, class Compare, class Alloc >
    bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }
	template< class Key, class T, class Compare, class Alloc >
    bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return rhs < lhs;
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif
