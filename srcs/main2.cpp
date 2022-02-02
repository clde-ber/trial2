#include "pair.hpp"

int main()
{
	ft::RBTree< int, int > bst;
    ft::Node< int, int > node0(0, 8);
    ft::Node< int, int > node1(1, 18);
    ft::Node< int, int > node2(2, 5);
    ft::Node< int, int > node3(3, 15);
    ft::Node< int, int > node4(4, 17);
    ft::Node< int, int > node5(5, 25);
    ft::Node< int, int > node6(6, 40);
    ft::Node< int, int > node7(7, 80);
    ft::Node< int, int > node8(8, 3);
    ft::Node< int, int > node9(9, 10);
	bst.insert(node0);
	bst.insert(node1);
	bst.insert(node2);
	bst.insert(node3);
	bst.insert(node4);
	bst.insert(node5);
	bst.insert(node6);
	bst.insert(node7);
	bst.insert(node8);
	bst.insert(node9);
	bst.prettyPrint();
	bst.deleteNode(node5.val);
	bst.deleteNode(node2.val);
	bst.deleteNode(node4.val);
	bst.deleteNode(node1.val);
	bst.deleteNode(node7.val);
	bst.deleteNode(node8.val);
	bst.deleteNode(node6.val);
	bst.deleteNode(node0.val);
	bst.deleteNode(node3.val);
	bst.deleteNode(node9.val);
	bst.deleteNode(node9.val);
    std::cout << "********" << std::endl;
	bst.prettyPrint();
	bst.freeNodes(bst.getRoot());
	return 0;
}