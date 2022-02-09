#ifndef PAIR3_H
#define PAIR3_H

#include <iostream>
#include <memory>
#include "Iter.hpp"

static int end = 0;

namespace ft
{
    template< class T1, class T2 >
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;
        pair() : first(first_type()), second(second_type()) {}
        pair( const T1& x, const T2& y ) : first(x), second(y) {}
        template<class U, class V>
        pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
        pair & operator=(pair const & rhs) { first = rhs.first; second = rhs.second; return *this; }
        pair<T1,T2> make_pair(T1 x, T2 y)
        {
            return pair<T1,T2>(x,y);
        }
        operator pair<const T1, T2 >() const
        {
            return pair< const T1, T2 >(first, second);
        }
    };
    template< class Key, class T >
    struct Leaf
    {
        Key first;
        T second;
        Leaf< Key, T > *parent; // pointer to the parent
        Leaf< Key, T > *left; // pointer to left child
        Leaf< Key, T > *right;
        int color; // 1 -> Red, 0 -> Black
        typedef Leaf< Key, T > value_type;
        typedef std::ptrdiff_t difference_type;
        typedef Leaf< Key, T >* pointer;
        typedef Leaf< Key, T >& reference;
        typedef bidirectional_iterator_tag iterator_category;

        Leaf() : first(Key()), second(T()), parent(NULL), left(NULL), right(NULL), color(0) {}
        Leaf(Leaf const & rhs) : first(rhs.first), second(rhs.second), parent(rhs.parent), left(rhs.left), right(rhs.right), color(rhs.color) {}
        Leaf( Key const & key, T const & val ) : first(key), second(val), parent(NULL), left(NULL), right(NULL), color(0) {}
        Leaf & operator=(Leaf const & rhs) { first = rhs.first; second = rhs.second; parent = rhs.parent; left = rhs.left; right = rhs.right; color = rhs.color; return *this; }
        virtual ~Leaf() {}
        Leaf< Key, T > make_leaf(Key const & key, T const & val)
        {
            return Leaf< Key, T >(key, val);
        }
        operator     Leaf<const Key, T>()
        {
            Leaf<const Key, T> leaf(first, second);
            leaf->parent = reinterpret_cast<Leaf<const Key, T> *>(parent);
            leaf->left = reinterpret_cast<Leaf<const Key, T> *>(left);
            leaf->right = reinterpret_cast<Leaf<const Key, T> *>(right);
            leaf->color = color;
            return (leaf);
        }
    };
    template< class Key, class T, class Compare, class alloc = std::allocator<Leaf< Key, T > > >
    class RBTree
    {
        public:
        typedef Compare                                         key_compare;
            class value_compare: public std::binary_function<pair<Key, T>,pair<Key, T>,bool> {
                friend class RBTree;
                protected:
                    Compare comp;

                public:
                    typedef	bool result_type;
                    typedef Key	first_argument_type;
                    typedef T	second_argument_type;
                    value_compare	(Compare c): comp(c) {};
                    bool	operator() (const pair<Key, T> &x, const pair< Key, T> &y) const
                    {
                        return comp(x.first, y.first);
                    }
            };
        private:

            // initializes the nodes with appropirate values
            // all the pointers are set to point to the null pointer
            void initializeNode(Leaf< Key, T > *node)
            {
                node->first = key_type();
                node->second = mapped_type();
                node->parent = NULL;
                node->left = NULL;
                node->right = NULL;
                node->color = 0;
            }
            void swap(Leaf< Key, T > **x, Leaf< Key, T > **y)
            {
                Leaf< Key, T > **tmp = x;
                x = y;
                y = tmp;
            }
        protected:
            typedef Key key_type;
            typedef T mapped_type;
            key_compare _key_compare;
            value_compare _value_compare;
            pair< Key, T > _pair_type;
            Leaf< Key, T > *root;
            Leaf< Key, T > *last;
        public:
            typedef Leaf< Key, T >* NodePtr;

            RBTree(key_compare comp) : _key_compare(comp), _value_compare(_key_compare), root(NULL), last(NULL) {}
            RBTree(RBTree const & rhs) : _key_compare(rhs._key_compare), _value_compare(rhs._value_compare), root(NULL), last(NULL) { (void)rhs; }
            RBTree & operator=(RBTree const & rhs) { _key_compare = rhs._key_compare; _value_compare = rhs._value_compare; root = NULL; last = NULL; (void)rhs; return *this; }
            virtual ~RBTree() {}
            NodePtr find(Leaf< Key, T> const & toFind)
            {
                NodePtr fromRoot = root;
                while (fromRoot)
                {
                    if (fromRoot == last)
                        return last;
                    if (_value_compare(_pair_type.make_pair(toFind.first, toFind.second), _pair_type.make_pair(fromRoot->first, fromRoot->second)))
                        fromRoot = fromRoot->left;
                    else if (!_value_compare(_pair_type.make_pair(toFind.first, toFind.second), _pair_type.make_pair(fromRoot->first, fromRoot->second)) && toFind.first != fromRoot->first)
                        fromRoot = fromRoot->right;
                    else
                        return fromRoot;
                }
                return last;
            }
            NodePtr findMinimum(NodePtr node) const
            {
                NodePtr origin = node;
                while (origin->left)
                    origin = origin->left;
                return origin;
            }
            NodePtr findMaximum(NodePtr node) const
            {
                NodePtr origin = node;
                while (origin->right && origin->right != last)
                    origin = origin->right;
                return origin;
            }
            void leftRotate(NodePtr x)
            {
                NodePtr y = x->right;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                //NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                NodePtr leftY = y->left;
                NodePtr parentX = x->parent;

                x->right = leftY;
                if (y->left)
                    y->left->parent = x;
                y->parent = parentX;
                if (!parentX)
                    root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                root->color = 0;
                y->left =  tmpX;
                x->parent = tmpY;
            }
            void rightRotate(NodePtr x)
            {
                NodePtr y = x->left;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                //NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                NodePtr rightY = y->right;
                NodePtr parentX = x->parent;

                x->left = rightY;
                if (y->right)
                    y->right->parent = x;
                y->parent = parentX;
                if (!parentX)
                    root = y;
                else if (x == x->parent->right)
                    x->parent->right = y;
                else
                    x->parent->left = y;
                root->color = 0;
                y->right =  tmpX;
                x->parent = tmpY;
            }
            void insert(Leaf< Key, T > const &toInsert)
            {
                NodePtr node = new Leaf< Key, T >;
                node->second = toInsert.second;
                node->first = toInsert.first;
                node->color = 1; // new node must be red
                
                NodePtr fromRoot = root;
                NodePtr parentNode = NULL;
                NodePtr child = NULL;
                while (fromRoot && fromRoot != last)
                {
                    parentNode = fromRoot;
                    if (_value_compare(_pair_type.make_pair(node->first, node->second), _pair_type.make_pair(fromRoot->first, fromRoot->second)))
                        fromRoot = fromRoot->left;
                    else if (!_value_compare(_pair_type.make_pair(node->first, node->second), _pair_type.make_pair(fromRoot->first, fromRoot->second)) && node->first != fromRoot->first)
                        fromRoot = fromRoot->right;
                    else
                        return ;
                    if (fromRoot)
                    {
                        child = fromRoot;
                        child->parent = parentNode;
                    }
                }
                node->parent = parentNode;
                if (!node->parent)
                {
                    root = node;
                    root->right = last;
                    last->parent = root;
                    node->color = 0;
                    return ;
                }
                if (_value_compare(_pair_type.make_pair(node->first, node->second), _pair_type.make_pair(root->first, root->second)))
                {
                    if (_value_compare(_pair_type.make_pair(node->first, node->second), _pair_type.make_pair(parentNode->first, parentNode->second)))
                        parentNode->left = node;
                    else if (!_value_compare(_pair_type.make_pair(node->first, node->second), _pair_type.make_pair(parentNode->first, parentNode->second)) && node->first != parentNode->first)
                        parentNode->right = node;
                    rightRotate(root);
                }
                else
                {
                    if (_value_compare(_pair_type.make_pair(node->first, node->second), _pair_type.make_pair(parentNode->first, parentNode->second)))
                        parentNode->left = node;
                    else if (!_value_compare(_pair_type.make_pair(node->first, node->second), _pair_type.make_pair(parentNode->first, parentNode->second)) && node->first != parentNode->first)
                        parentNode->right = node;
                    leftRotate(root);
                }
                NodePtr max = findMaximum(root);
                max->right = last;
                last->parent = max;
                if (node->parent)
                    recolor(root);
            }
            NodePtr getRoot() const
            {
                return root;
            }
            NodePtr getLast() const
            {
                return last;
            }
            void setLast(NodePtr node)
            {
                last = node;
            }
            void recolor (NodePtr node)
            {
                if (node != NULL)
                {
                    if (node->left && node->left->color)
                    {
                        if (node->left->right)
                            node->left->right->color = 0;
                        if (node->left->left)
                            node->left->left->color = 0;
                    }
                    if (node->right && node->right->color)
                    {
                        if (node->right->right)
                            node->right->right->color = 0;
                        if (node->right->left)
                            node->right->left->color = 0;
                    }
                    recolor(node->left);
                    recolor(node->right);
                }
                if (root->right)
                    root->right->color = 0;
                if (root->left)
                    root->left->color = 0;
            }
            int isDeletable(NodePtr found)
            {
                if (!found->parent && !found->left && found->right && found->right == last)
                {
                    initializeNode(found);
                    initializeNode(last);
                    initializeNode(root);
                    delete found;
                    found = NULL;
                    root = NULL;
                    end = 1;
                    return 1;
                }
                if (!found->parent && found->right && found->right == last && found->left)
                {
                    root = found->left;
                    root->parent = NULL;
                    initializeNode(found);
                    delete found;
                    found = NULL;
                    NodePtr max = findMaximum(root);
                    max->right = last;
                    last->parent = max;
                    return 1;
                }
                if (!found->parent && !found->left && found->right && found->right != last)
                {
                    found->right->parent = NULL;
                    root = found->right;
                    root->parent = NULL;
                    initializeNode(found);
                    delete found;
                    found = NULL;
                    NodePtr max = findMaximum(root);
                    max->right = last;
                    last->parent = max;
                    return 1;
                }
                if (found->left && found->right && found->right != last && !found->left->left && !found->left->right && !found->right->left && found->right->right == last)
                    {
                        if (found == found->parent->right)
                        {
                            found->parent->right = found->right;
                            found->right->parent = found->parent;
                            found->parent->right->left = found->left;
                            found->left->parent = found->parent->right;
                        }
                        else
                        {
                            found->parent->left = found->right;
                            found->right->parent = found->parent;
                            found->parent->left->left = found->left;
                            found->left->parent = found->parent->left;
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        NodePtr max = findMaximum(root);
                        max->right = last;
                        last->parent = max;
                        return 1;
                    }
                    if (found->left && found->right && found->right == last)
                    {
                        if (found == found->parent->right)
                        {
                            found->parent->right = found->left;
                            found->left->parent = found->parent;
                        }
                        else
                        {
                            found->parent->left = found->left;
                            found->left->parent = found->parent;
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        NodePtr max = findMaximum(root);
                        max->right = last;
                        last->parent = max;
                        return 1;
                    }
                    if (found->right && found->right != last && !found->left)
                    {
                        if (found == found->parent->right)
                        {
                            found->parent->right = found->right;
                            found->right->parent = found->parent;
                        }
                        else
                        {
                            found->parent->left = found->right;
                            found->right->parent = found->parent;
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        NodePtr max = findMaximum(root);
                        max->right = last;
                        last->parent = max;
                        return 1;
                    }
                    if (found->right && found->right == last && !found->left)
                    {
                        if (found == found->parent->right)
                        {
                            found->parent->right = NULL;
                            found->parent = NULL;
                        }
                        else
                        {
                            found->parent->left = NULL;
                            found->parent = NULL;
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        NodePtr max = findMaximum(root);
                        max->right = last;
                        last->parent = max;
                        return 1;
                    }
                    return 0;
            }
            void deleteNode(Key value)
            {
                NodePtr found = NULL;
                NodePtr node = getRoot();
                int i = 0;
                while (node)
                {
                    if (node->first == value)
                        found = node;
                    if (!_value_compare(_pair_type.make_pair(value, T()), _pair_type.make_pair(node->first, node->second)) && node->first != value)
                        node = node->left;
                    else
                        node = node->right;
                }
                if (!found || (found && !found->parent))
                {
                    if (!found)
                        return ;
                    else
                    {
                        i = isDeletable(found);
                        while (root && root->left && !i)
                        {
                            i = isDeletable(found);
                            if (i)
                                return ;
                            rightRotate(root);
                        }
                        while (root && root->right && !i)
                        {
                            i = isDeletable(found);
                            if (i)
                                return ;
                            leftRotate(root);
                        }
                    }
                    return ;
                }
                if (_value_compare(_pair_type.make_pair(value, T()), _pair_type.make_pair(found->parent->first, found->parent->second)))
                {
                    while (found && found->left)
                    {
                        i = isDeletable(found);
                        if (i)
                        {
                            if (root && end == 0)
                                recolor(root);
                            break ;
                        }
                        rightRotate(found);
                    }
                }
                else
                {
                    while (found && found->right)
                    {
                        i = isDeletable(found);
                        if (i)
                        {
                            if (root && end == 0)
                                recolor(root);
                            break ;
                        }
                        leftRotate(found);
                    }
                }
              if (!i || found == root)
                isDeletable(found);
            }
            void printHelper(NodePtr root, std::string indent, bool last) const
            {
                // print the tree structure on the screen
                if (root != NULL)
                {
                    std::cout<<indent;
                    if (last)
                    {
                        std::cout<<"R----";
                        indent += "     ";
                    }
                    else
                    {
                        std::cout<<"L----";
                        indent += "|    ";
                    }
                    std::string sColor = root->color?"RED":"BLACK";
                    std::cout<<root->first<<"("<<sColor<<")"<<std::endl;
                    printHelper(root->left, indent, false);
                    printHelper(root->right, indent, true);
                }
            }
            void prettyPrint() const
            {
                if (root)
                    printHelper(this->root, "", true);
	        }
            void freeNodes(NodePtr node)
            {
                if (node != NULL)
                {
                    freeNodes(node->left);
                    freeNodes(node->right);
                }
                delete node;
                node = NULL;
            }
            // If a node is red, both of its children are black. This means no two nodes on a path can be red nodes.
            // Every path from a root node to a NULL node has the same number of black nodes.
    };
    template< class T1, class T2 >
    bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        return lhs.first == rhs.first && lhs.second == lhs.second;
    }
    template< class T1, class T2 >
    bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        return !(lhs == rhs);
    }
    template< class T1, class T2 >
    bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        if (lhs.first < rhs.first)
            return 1;
        if (rhs.first < lhs.first)
            return 0;
        if (lhs.second < rhs.second)
            return 1;
        return 0; 
    }
    template< class T1, class T2 >
    bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        return !(rhs < lhs);
    }
    template< class T1, class T2 >
    bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        return rhs < lhs;
    }
    template< class T1, class T2 >
    bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        return !(lhs < rhs);
    }

    template< class T1, class T2 >
    bool operator==( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        return lhs.first == rhs.first && lhs.second == lhs.second;
    }
    template< class T1, class T2 >
    bool operator!=( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        return !(lhs == rhs);
    }
    template< class T1, class T2 >
    bool operator<( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        if (lhs.first < rhs.first)
            return 1;
        if (rhs.first < lhs.first)
            return 0;
        if (lhs.second < rhs.second)
            return 1;
        return 0; 
    }
    template< class T1, class T2 >
    bool operator<=( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        return !(rhs < lhs);
    }
    template< class T1, class T2 >
    bool operator>( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        return rhs < lhs;
    }
    template< class T1, class T2 >
    bool operator>=( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        return !(lhs < rhs);
    }
}

//https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

#endif

/*T current = _it;

                if (_it->right && !_it->right->right)
                {
                    current = _it->parent;
                    while (current && current->first < _it->first)
                        current = current->parent;
                    _it = current;
                }
                else
                {
                    current = _it->right;
                    if (current->right && !current->right->right)
                        _it = current;
                    else
                    {
                        while (current->left && current->left->right && current->left->right->right)
                            current = current->left;
                    }
                    _it = current;
                }
                return _it;*/