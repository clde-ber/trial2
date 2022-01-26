#ifndef MAP_H
#define MAP_H

namespace ft
{
    template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
    class map
    {
        typedef Key key_type;
        typedef T mapped_type;
        typedef pair<const Key, T> value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef Allocator::pointer pointer;
        typedef Allocator::const_pointer const_pointer;
        typedef LegacyBidirectionalIterator iterator;
        typedef LegacyBidirectionalIterator const_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        class value_compare
        {
            private:
                bool result_type;
                value_type first_argument_type;
                value_type second_argument_type;
            protected:
                Compare comp;
                value_compare(Compare c) {comp = c}
            public:
                bool operator()( const value_type& lhs, const value_type& rhs ) const {return !(lhs < rhs) && !(rhs < lhs);}
        };
        public:
            map()
            {

            }
            explicit map(const Compare& comp, const Allocator& alloc = Allocator())
            {

            }
            template< class InputIt > map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
            {

            }
            ~map();
            map& operator=(const map& other)
            {

            }
            allocator_type get_allocator() const
            {

            }
            T& at(const Key& key)
            {

            }
            const T& at(const Key& key) const
            {

            }
            T& operator[](const Key& key)
            {

            }
            bool empty() const
            {

            }
            size_type size() const
            {

            }
            size_type max_size() const
            {

            }
            void clear()
            {

            }
            pair<iterator, bool> insert(const value_type& value)
            {

            }
            iterator insert(iterator hint, const value_type& value)
            {

            }
            template< class InputIt >
            void insert(InputIt first, InputIt last)
            {

            }
            void erase(iterator pos)
            {

            }
            void erase(iterator first, iterator last)
            {

            }
            size_type erase(const Key& key)
            {

            }
            void swap(map& other)
            {

            }
            size_type count(const Key& key) const
            {

            }
            iterator find(const Key& key)
            {

            }	
            const_iterator find(const Key& key) const
            {
                
            }
            pair<iterator,iterator> equal_range(const Key& key)
            {

            }
            pair<const_iterator,const_iterator> equal_range(const Key& key) const
            {

            }
            iterator lower_bound(const Key& key)
            {

            }
            const_iterator lower_bound(const Key& key) const
            {

            }
            iterator upper_bound(const Key& key)
            {

            }
            const_iterator upper_bound(const Key& key) const
            {

            }
            key_compare key_comp() const
            {

            }
            map::value_compare value_comp() const
            {

            }
    };

    template< class Key, class T, class Compare, class Alloc >
    bool operator==(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs);	
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs);
    template< class Key, class T, class Compare, class Alloc >
    bool operator<(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs);
	template< class Key, class T, class Compare, class Alloc >
    bool operator<=(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs);
	template< class Key, class T, class Compare, class Alloc >
    bool operator>(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs);
    template< class Key, class T, class Compare, class Alloc >
    bool operator>=(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs);
}

#endif