#include "red_black_tree.hpp"

int main() {

	ft::RedBlackTree<int> yo;

	// yo.insert(5);
	// yo.insert(2);
	// yo.insert(6);
	// yo.insert(9);
	yo.insert(17);
	yo.insert(12);
	yo.insert(96);
	yo.insert(1);
	yo.insert(3);
	yo.insert(42);
	yo.insert(37);
	yo.insert(25);

	ft::RBTIterator<int> it = yo.begin();
	ft::RBTIterator<int> ite = yo.end();

	// for (; it != ite; it++) {
	// 	std::cout << *it << ", ";
	// }
	std::cout << std::endl;
	std::cout << "ROOT = " << yo.getRoot()->_data << std::endl;
	yo._InOrder(yo.getRoot());
	return 0;

};