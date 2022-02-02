#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

static int end = 0;

namespace ft
{
    template< class Key, class T >
    class Node
        {
            private:
                Key data; // holds the key
                T val;
                Node *parent; // pointer to the parent
                Node *left; // pointer to left child
                Node *right; // pointer to right child
                int color; // 1 -> Red, 0 -> Black
            public:
                Node() : data(0), val(0), parent(0), left(0), right(0), color(0) {}
                Node(Key key, T value) : data(key), val(value), parent(0), left(0), right(0), color(0) {}
                Node(Node const & rhs) : data(rhs.data), val(rhs.val), parent(rhs.parent), left(rhs.left), right(rhs.right), color(0) {}
                Node & operator=(Node const & rhs) {new(this) Node(rhs); return *this;}
                virtual ~Node() { data = 0; val = 0; parent = NULL; left = NULL; right = NULL; color = 0; }
                Key getData() const {return data;}
                T getVal() const {return val;}
                Node *getParent() const {return parent;}
                Node *getLeft() const {return left;}
                Node *getRight() const {return right;}
                int getColor() const {return color;}
                void setData(Key key) {data = key;}
                void setVal(T value) {val = value;}
                void setParent(Node *rhs) {parent = rhs;}
                void setLeft(Node *rhs) {left = rhs;}
                void setRight(Node *rhs) {right = rhs;}
                void setColor(int col) {color = col;}
        };
    template< class Key, class T >
    class RBTree
    {
        private:
            Node< Key, T > *root = NULL;

            // initializes the nodes with appropirate values
            // all the pointers are set to point to the null pointer
            void initializeNode(Node< Key, T > *node)
            {
                node->setData(0);
                node->setVal(0);
                node->setParent(NULL);
                node->setLeft(NULL);
                node->setRight(NULL);
                node->setColor(0);
            }
            void swap(Node< Key, T  > **x, Node< Key, T > **y)
            {
                Node< Key, T > **tmp = x;
                x = y;
                y = tmp;
            }
        public:
            typedef Node< Key, T >* NodePtr;

            RBTree() : root(0) {}
            template< typename U >
            RBTree(const Node< Key, T >& value) : root(0) { insert(value); }
            RBTree(RBTree const & rhs) : root(0) { (void)rhs; }
            //template< class InputIt >
            //RBTree(InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL) : root(0) { while (first != last) { insert(*first); first++; } }
            RBTree & operator=(RBTree const & rhs) { root = 0; new(this) RBTree(rhs); return *this; }
            virtual ~RBTree() {}
            NodePtr find(Node<Key, T> const& toFind) const
            {
                NodePtr fromRoot = root;
                while (fromRoot)
                {
                    if (toFind.getData() < fromRoot->getData() && toFind.getVal() != fromRoot->getVal())
                        fromRoot = fromRoot->getLeft();
                    else if (toFind.getData() > fromRoot->getData() && toFind.getVal() != fromRoot->getVal())
                        fromRoot = fromRoot->getRight();
                    else
                        break ;
                }
                return fromRoot;
            }
            void leftRotate(NodePtr x)
            {
                NodePtr y = x->getRight();

                NodePtr tmpY = y;
                NodePtr tmpX = x;
                NodePtr rightY = y->getRight();
                NodePtr leftX = x->getLeft();
                NodePtr leftY = y->getLeft();
                NodePtr parentX = x->getParent();

                y->setParent(parentX);
                y->setRight(rightY);
                y->setLeft(tmpX);
                x->setParent(tmpY);
                x->setRight(leftY);
                x->setLeft(leftX);
                if (!x->getParent())
                    root = x;
                if (!y->getParent())
                    root = y;
                root->setColor(0);
            }
            void rightRotate(NodePtr y)
            {
                NodePtr x = y->getLeft();
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                NodePtr rightX = x->getRight();
                NodePtr rightY = y->getRight();
                NodePtr leftX = x->getLeft();
                NodePtr parentY = y->getParent();

                y->setParent(tmpX);
                y->setLeft(rightX);
                y->setRight(rightY);
                x->setLeft(leftX);
                x->setRight(tmpY);
                x->setParent(parentY);
                if (!x->getParent())
                    root = x;
                if (!y->getParent())
                    root = y;
                root->setColor(0);
            }
            void insert(Node< Key, T > const &toInsert)
            {
                NodePtr node = new Node< Key, T >(toInsert);
                initializeNode(node);
                node->setData(toInsert.getData());
                node->setVal(toInsert.getVal());
                node->setColor(1); // new node must be red
                
                NodePtr fromRoot = root;
                NodePtr parentNode = NULL;
                NodePtr child = NULL;
                while (fromRoot)
                {
                    parentNode = fromRoot;
                    if (node->getVal() < fromRoot->getVal())
                        fromRoot = fromRoot->getLeft();
                    else
                        fromRoot = fromRoot->getRight();
                    if (fromRoot)
                    {
                        child = fromRoot;
                        child->setParent(parentNode);
                    }
                }
                node->setParent(parentNode);
                if (!node->getParent())
                {
                    root = node;
                    node->setColor(0);
                    return ;
                }
                if (node->getVal() < root->getVal())
                {
                    if (node->getVal() < parentNode->getVal())
                        parentNode->setLeft(node);
                    else
                        parentNode->setRight(node);
                    rightRotate(root);
                }
                else
                {
                    if (node->getVal() < parentNode->getVal())
                        parentNode->setLeft(node);
                    else
                        parentNode->setRight(node);
                    leftRotate(root);
                }
                if (node->getParent())
                recolor(getRoot());
            }
            NodePtr getRoot()
            {
                return root;
            }
            void recolor (NodePtr node)
            {
                if (node != NULL)
                {
                    if (node->getLeft() && node->getLeft()->getColor())
                    {
                        if (node->getLeft()->getRight())
                            node->getLeft()->getRight()->setColor(0);
                        if (node->getLeft()->getLeft())
                            node->getLeft()->getLeft()->setColor(0);
                    }
                    if (node->getRight() && node->getRight()->getColor())
                    {
                        if (node->getRight()->getRight())
                            node->getRight()->getRight()->setColor(0);
                        if (node->getRight()->getLeft())
                            node->getRight()->getLeft()->setColor(0);
                    }
                    recolor(node->getLeft());
                    recolor(node->getRight());
                }
                if (root->getRight())
                    root->getRight()->setColor(0);
                if (root->getLeft())
                    root->getLeft()->setColor(0);
            }
            int isDeletable(NodePtr found)
            {
                //if (found->getParent())
                //std::cout << found->getVal() << found->getParent()->getVal() << " " << found->getRight() << " " << found->getLeft() << std::endl;
                if (!found->getParent() && !found->getLeft() && !found->getRight())
                {
                    initializeNode(found);
                    initializeNode(root);
                    delete found;
                    found = NULL;
                    root = NULL;
                    end = 1;
                    return 1;
                }
                if (found->getVal() == root->getVal())
                    return 0;
                if (found->getLeft() && found->getRight() && !found->getLeft()->getLeft() && !found->getLeft()->getRight() && !found->getRight()->getLeft() && !found->getRight()->getRight())
                    {
                        if (found == found->getParent()->getRight())
                        {
                            found->getParent()->setRight(found->getRight());
                            found->getRight()->setParent(found->getParent());
                            found->getParent()->getRight()->setLeft(found->getLeft());
                            found->getLeft()->setParent(found->getParent()->getRight());
                        }
                        else
                        {
                            found->getParent()->setLeft(found->getRight());
                            found->getRight()->setParent(found->getParent());
                            found->getParent()->getLeft()->setLeft(found->getLeft());
                            found->getLeft()->setParent(found->getParent()->getLeft());
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        return 1;
                    }
                    if (found->getLeft() && !found->getRight())
                    {
                        if (found == found->getParent()->getRight())
                        {
                            found->getParent()->setRight(found->getLeft());
                            found->getLeft()->setParent(found->getParent());
                        }
                        else
                        {
                            found->getParent()->setLeft(found->getLeft());
                            found->getLeft()->setParent(found->getParent());
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        return 1;
                    }
                    if (found->getRight() && !found->getLeft())
                    {
                        if (found == found->getParent()->getRight())
                        {
                            found->getParent()->setRight(found->getRight());
                            found->getRight()->setParent(found->getParent());
                        }
                        else
                        {
                            found->getParent()->setLeft(found->getRight());
                            found->getRight()->setParent(found->getParent());
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        return 1;
                    }
                    if (!found->getRight() && !found->getLeft())
                    {
                        if (found == found->getParent()->getRight())
                        {
                            found->getParent()->setRight(NULL);
                        }
                        else
                        {
                            found->getParent()->setLeft(NULL);
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        return 1;
                    }
                    return 0;
            }
            void deleteNode(T value)
            {
                NodePtr found = NULL;
                NodePtr node = getRoot();
                while (node)
                {
                    if (node->getVal() == value)
                        found = node;
                    if (value <= node->getVal())
                        node = node->getLeft();
                    else
                        node = node->getRight();
                }
                int alreadydeleted = 0;
                int alreadydeleted2 = 0;
                if (found)
                    std::cout << "found key " << found->getData() << "| found value " << found->getVal() << "| value " << value << std::endl;
                if (!found)
                    return ;
                if (value >= root->getVal())
                {
                    while (found && found->getLeft() && found->getLeft()->getLeft() && found->getLeft()->getRight())
                    {
                        if (isDeletable(found))
                            alreadydeleted = 1;
                        rightRotate(found);
                    }
                    if (!alreadydeleted)
                    {
                        if (found == root)
                        {
                            while (root->getLeft() && !alreadydeleted2)
                            {rightRotate(root);
                            if (isDeletable(found))
                            alreadydeleted2 = 1;
                            prettyPrint();}
                            while (root->getRight() && !alreadydeleted2)
                            {leftRotate(root);
                            if (isDeletable(found))
                            alreadydeleted2 = 1;
                            prettyPrint();}
                        }
                    }
                }
                else
                {
                    while (found && found->getRight() && found->getRight()->getLeft() && found->getRight()->getRight())
                    {
                        if (isDeletable(found))
                            alreadydeleted = 1;
                        leftRotate(found);
                    }
                    if (!alreadydeleted)
                    {
                        if (found == root)
                        {
                            while (root->getRight() && !alreadydeleted2)
                            {leftRotate(root);
                            if (isDeletable(found))
                            alreadydeleted2 = 1;
                            prettyPrint();}
                            while (root->getLeft() && !alreadydeleted2)
                            {rightRotate(root);
                            if (isDeletable(found))
                            alreadydeleted2 = 1;
                            prettyPrint();}
                        }
                    }
                }
                if (!alreadydeleted && !alreadydeleted2 && end == 0)
                    isDeletable(found);
                prettyPrint();
                if (root && end == 0)
                    recolor(root);
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
                    std::string sColor = root->getColor()?"RED":"BLACK";
                    std::cout<<root->getVal()<<"("<<sColor<<")"<<std::endl;
                    printHelper(root->getLeft(), indent, false);
                    printHelper(root->getRight(), indent, true);
                }
            }
            void prettyPrint()
            {
                if (root)
                    printHelper(getRoot(), "", true);
	        }
            void freeNodes(NodePtr node)
            {
                if (node != NULL)
                {
                    freeNodes(node->getLeft());
                    freeNodes(node->getRight());
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