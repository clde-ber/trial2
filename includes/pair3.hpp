#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <memory>

static int end = 0;

namespace ft
{
    template< class Key, class T >
    struct pair
    {
        typedef Key key_type;
        typedef T mapped_type;
        Key first; // holds the key
        T second;
        pair *parent; // pointer to the parent
        pair *left; // pointer to left child
        pair *right; // pointer to right child
        int color; // 1 -> Red, 0 -> Black
        pair() : first(key_type()), second(mapped_type()), parent(NULL), left(NULL), right(NULL), color(0) {}
        pair(Key key, T value) : first(key), second(value), parent(NULL), left(NULL), right(NULL), color(0) {}
        pair(pair const & rhs) : first(rhs.first), second(rhs.second), parent(NULL), left(NULL), right(NULL), color(rhs.color) {}
        pair & operator=(pair const & rhs) { first = rhs.first; second = rhs.second; parent = NULL; left = NULL; right = NULL; return *this; }
    };
    template< class Key, class T, class Compare, class alloc = std::allocator<pair< Key, T > > >
    class RBTree
    {
        private:
            pair< Key, T > *root = NULL;
            pair< Key, T > *last = NULL;
            typedef Key key_type;
            typedef T mapped_type;

            // initializes the nodes with appropirate values
            // all the pointers are set to point to the null pointer
            void initializeNode(pair< Key, T > *node)
            {
                node->first = key_type();
                node->second = mapped_type();
                node->parent = NULL;
                node->left = NULL;
                node->right = NULL;
                node->color = 0;
            }
            void swap(pair< Key, T > **x, pair< Key, T > **y)
            {
                pair< Key, T > **tmp = x;
                x = y;
                y = tmp;
            }
        public:
            typedef Compare                                         key_compare;
            class value_compare: public std::binary_function<T,T,bool> {
                friend class RBTree;
                protected:
                    Compare comp;
                    value_compare	(Compare c): comp(c) {};

                public:
                    typedef	bool result_type;
                    typedef T	first_argument_type;
                    typedef T	second_argument_type;
                    value_compare	(value_compare const & c): comp(c.comp) {};
                    bool	operator() (const T &x, const T &y) const
                    {
                        return comp(x.first, y.first);
                    }
            };
            typedef pair< Key, T >* NodePtr;

            NodePtr find(pair<Key, T> const& toFind) const
            {
                NodePtr fromRoot = root;
                while (fromRoot)
                {
                    if (fromRoot == last)
                        return last;
                    if (toFind.second < fromRoot->second)
                        fromRoot = fromRoot->left;
                    else if (toFind.second > fromRoot->second)
                        fromRoot = fromRoot->right;
                    else
                        return fromRoot;
                }
                return last;
            }
            NodePtr findMinimum(NodePtr node) const
            {
                NodePtr origin = node;
                while (origin->left && origin->left != last)
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
                y->left =  tmpX;
                x->parent = tmpY;
                y->parent = parentX;
                if (!parentX)
                    root = y;
                else
                    y->parent->right = y;    
                root->color = 0;
            }
            void rightRotate(NodePtr y)
            {
                NodePtr x = y->left;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                //NodePtr leftX = x->left;
                NodePtr parentY = y->parent;

                x->right = tmpY;
                y->left =  rightX;
                x->parent = parentY;
                y->parent = tmpX;
               //x->parent->left = x;
                if (!parentY)
                    root = x;
                else
                  x->parent->left = x;    
                root->color = 0;
            }
            /*void leftRotate(NodePtr x)
            {
                NodePtr y = x->right;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                //NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                NodePtr leftY = y->left;
                NodePtr parentX = x->parent;

                if (leftY != last)
                    x->right = leftY;
                else
                    x->right = NULL;
                if (tmpX != last)
                    y->left =  tmpX;
                else
                    y->left = NULL;
                if (tmpY != last)
                    x->parent = tmpY;
                else
                    x->parent = NULL;
                if (parentX != last)
                    y->parent = parentX;
                else
                    y->parent = NULL;
                if (!parentX)
                {
                    root = y;
           //         root->parent = last;
           //         last->left = root;
                }
                else
                    y->parent->right = y; 
               NodePtr max = findMaximum(root);
                initializeNode(last);
                max->right = last;
                last->parent = max;
                prettyPrint();
                root->color = 0;
            }
            void rightRotate(NodePtr y)
            {
                NodePtr x = y->left;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                //NodePtr leftX = x->left;
                NodePtr parentY = y->parent;

                if (tmpY != last)
                x->right = tmpY;
                else
                x->right = NULL;
                if (rightX != last)
                y->left =  rightX;
                else
                y->left = NULL;
                if (parentY != last)
                x->parent = parentY;
                else
                x->parent = NULL;
                if (tmpX != last)
                y->parent = tmpX;
                else
                y->parent = NULL;
               //x->parent->left = x;
                if (!parentY)
                {
                    root = x;
          //          root->parent = last;
          //          last->left = root;
                }
                else
                  x->parent->left = x;    
                NodePtr max = findMaximum(root);
                initializeNode(last);
                max->right = last;
                last->parent = max;  
                prettyPrint();
                root->color = 0;
            }*/
            void insert(pair< Key, T > const &toInsert)
            {
                NodePtr node = new pair< Key, T >;
                node->second = toInsert.second;
                node->first = toInsert.first;
                node->color = 1; // new node must be red
                
                NodePtr fromRoot = root;
                NodePtr parentNode = NULL;
                NodePtr child = NULL;
                while (fromRoot && fromRoot != last)
                {
                    parentNode = fromRoot;
                    if (node->second < fromRoot->second)
                        fromRoot = fromRoot->left;
                    else
                        fromRoot = fromRoot->right;
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
                if (node->second < root->second)
                {
                    if (node->second < parentNode->second)
                        parentNode->left = node;
                    else
                        parentNode->right = node;
                    rightRotate(root);
                }
                else
                {
                    if (node->second < parentNode->second)
                        parentNode->left = node;
                    else
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
            void deleteNode(T value)
            {
                NodePtr found = NULL;
                NodePtr node = getRoot();
                int i = 0;
                while (node)
                {
                    if (node->second == value)
                        found = node;
                    if (value <= node->second)
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
                if (value < found->parent->second)
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
            void printHelper(NodePtr root, std::string indent, bool last)
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
                    std::cout<<root->second<<"("<<sColor<<")"<<std::endl;
                    printHelper(root->left, indent, false);
                    printHelper(root->right, indent, true);
                }
            }
            void prettyPrint()
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
}

//https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

#endif