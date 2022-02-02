#include "pair.hpp"

int main()
{
	ft::RBTree< int, int > bst;
	ft::Node< int, int > i1(0, 8);
	ft::Node< int, int > i2(1, 18);
	ft::Node< int, int > i3(2, 5);
	ft::Node< int, int > i4(3, 15);
	ft::Node< int, int > i5(4, 17);
	ft::Node< int, int > i6(5, 25);
	ft::Node< int, int > i7(6, 40);
	ft::Node< int, int > i8(7, 80);
	ft::Node< int, int > i9(8, 3);
	ft::Node< int, int > i10(9, 10);
	bst.insert(i1);
	bst.insert(i2);
	bst.insert(i3);
	bst.insert(i4);
	bst.insert(i5);
	bst.insert(i6);
	bst.insert(i7);
	bst.insert(i8);
	bst.insert(i9);
	bst.insert(i10);
	bst.prettyPrint();
	bst.deleteNode(i1.val);
	bst.deleteNode(i2.val);
	bst.deleteNode(i3.val);
	bst.deleteNode(i4.val);
	bst.deleteNode(i5.val);
	bst.deleteNode(i6.val);
	bst.deleteNode(i7.val);
	bst.deleteNode(i8.val);
	bst.deleteNode(i9.val);
	bst.deleteNode(i10.val);
	bst.deleteNode(i10.val);
	std::cout << "*****" << std::endl;
	bst.prettyPrint();
	return 0;
}