#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

static int end = 0;

namespace ft
{
    template< class Key >
    struct Node
    {
        Key data; // holds the key
        Node *parent; // pointer to the parent
        Node *left; // pointer to left child
        Node *right; // pointer to right child
        int color; // 1 -> Red, 0 -> Black
    };

    template< class Key, class T >
    class RBTree
    {
        private:
            Node< Key > *root = NULL;

            // initializes the nodes with appropirate values
            // all the pointers are set to point to the null pointer
            void initializeNode(Node< Key > *node)
            {
                node->data = 0;
                node->parent = NULL;
                node->left = NULL;
                node->right = NULL;
                node->color = 0;
            }
            void swap(Node< Key > **x, Node< Key > **y)
            {
                Node< T > **tmp = x;
                x = y;
                y = tmp;
            }
        public:
            typedef Node< Key >* NodePtr;

            void leftRotate(NodePtr x)
            {
                NodePtr y = x->right;

                NodePtr tmpY = y;
                NodePtr tmpX = x;
                NodePtr rightY = y->right;
                NodePtr leftX = x->left;
                NodePtr leftY = y->left;
                NodePtr parentX = x->parent;

                y->parent = parentX;
                y->right = rightY;
                y->left = tmpX;
                x->parent = tmpY;
                x->right = leftY;
                x->left = leftX;
                if (!x->parent)
                    root = x;
                if (!y->parent)
                    root = y;
                root->color = 0;
            }
            void rightRotate(NodePtr y)
            {
                NodePtr x = y->left;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                NodePtr rightX = x->right;
                NodePtr rightY = y->right;
                NodePtr leftX = x->left;
                NodePtr parentY = y->parent;

                y->parent = tmpX;
                y->left = rightX;
                y->right = rightY;
                x->left = leftX;
                x->right = tmpY;
                x->parent = parentY;
                if (!x->parent)
                    root = x;
                if (!y->parent)
                    root = y;
                root->color = 0;
            }
            void insert(int key)
            {
                NodePtr node = new Node< Key >;
                initializeNode(node);
                node->data = key;
                node->color = 1; // new node must be red
                
                NodePtr fromRoot = root;
                NodePtr parentNode = NULL;
                NodePtr child = NULL;
                while (fromRoot)
                {
                    parentNode = fromRoot;
                    if (node->data < fromRoot->data)
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
                    node->color = 0;
                    return ;
                }
                if (node->data < root->data)
                {
                    if (node->data < parentNode->data)
                        parentNode->left = node;
                    else
                        parentNode->right = node;
                    rightRotate(root);
                }
                else
                {
                    if (node->data < parentNode->data)
                        parentNode->left = node;
                    else
                        parentNode->right = node;
                    leftRotate(root);
                }
                if (node->parent)
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
                if (!found->parent && !found->left && !found->right)
                {
                    initializeNode(found);
                    delete found;
                    found = NULL;
                    root = NULL;
                    end = 1;
                    return 1;
                }
                if (found == root)
                    return 0;
                if (found->left && found->right && !found->left->left && !found->left->right && !found->right->left && !found->right->right)
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
                        return 1;
                    }
                    else if (found->left && !found->right)
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
                        return 1;
                    }
                    else if (found->right && !found->left)
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
                        return 1;
                    }
                    else if (!found->right && !found->left)
                    {
                        if (found == found->parent->right)
                        {
                            found->parent->right = NULL;
                        }
                        else
                        {
                            found->parent->left = NULL;
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        return 1;
                    }
                    return 0;
            }
            void deleteNode(int key)
            {
                NodePtr found = NULL;
                NodePtr node = getRoot();
                int i = 0;
                int count = i;
                while (node)
                {
                    if (node->data == key)
                        found = node;
                    if (key <= node->data)
                        node = node->left;
                    else
                        node = node->right;
                    i++;
                }
                count = i;
                if (!found)
                    return ;
                int alreadydeleted = 0;
                int alreadydeleted2 = 0;
                if (key > root->data)
                {
                    while (found && found->left && found->left->left && found->left->right && !isDeletable(found))
                    {
                        rightRotate(found);
                        alreadydeleted = 1;
                    }
                    if (!alreadydeleted)
                    {
                        if (found == root)
                        {
                            while (found == root && root->left && !isDeletable(found))
                            {rightRotate(found);
                            alreadydeleted2 = 1;}
                            while (found == root && root->right && !isDeletable(found))
                            {leftRotate(root);
                            alreadydeleted2 = 1;}
                        }
                    }
                }
                else
                {
                    while (found && found->right && found->right->left && found->right->right && !isDeletable(found))
                    {
                        leftRotate(found);
                        alreadydeleted = 1;
                    }
                    if (!alreadydeleted)
                    {
                        if (found == root)
                        {
                            while (found == root && root->right && !isDeletable(found))
                            {leftRotate(root);
                            alreadydeleted2 = 1;}
                            while (found == root && root->left && !isDeletable(found))
                            {rightRotate(found);
                            alreadydeleted2 = 1;}
                        }
                    }
                }
                if (!alreadydeleted && end == 0)
                    isDeletable(found);
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
                    std::string sColor = root->color?"RED":"BLACK";
                    std::cout<<root->data<<"("<<sColor<<")"<<std::endl;
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