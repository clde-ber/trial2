#include "pair3.hpp"

int main()
{
	ft::RBTree< int, int > bst;
    ft::pair< int, int > node0(0, 8);
    ft::pair< int, int > node1(1, 18);
    ft::pair< int, int > node2(2, 5);
    ft::pair< int, int > node3(3, 15);
    ft::pair< int, int > node4(4, 17);
    ft::pair< int, int > node5(5, 25);
    ft::pair< int, int > node6(6, 40);
    ft::pair< int, int > node7(7, 80);
    ft::pair< int, int > node8(8, 3);
    ft::pair< int, int > node9(9, 10);
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
	bst.deleteNode(node5.second);
	bst.deleteNode(node2.second);
	bst.deleteNode(node4.second);
	bst.deleteNode(node1.second);
	bst.deleteNode(node7.second);
	bst.deleteNode(node8.second);
	bst.deleteNode(node6.second);
	bst.deleteNode(node0.second);
	bst.deleteNode(node3.second);
	bst.deleteNode(node9.second);
	//bst.deleteNode(node9.val);
    std::cout << "********" << std::endl;
	bst.prettyPrint();
	//bst.freeNodes(bst.getRoot());
	return 0;
}