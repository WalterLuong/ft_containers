#include "red_black_tree.hpp"

int main() {

	ft::RedBlackTree<int, std::less<int>> yo;

	yo.insert(5);
	yo.insert(12);
	yo.insert(96);
	yo.insert(1);
	yo.insert(3);
	yo.insert(42);
	yo.insert(37);
	yo.insert(25);

	ft::RBTIterator<int> it = yo.begin();
	ft::RBTIterator<int> ite = yo.end();

	for (; it != ite; it++) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
	std::cout << "ROOT = " << yo.getRoot()->_data << std::endl;
	// yo._InOrder(yo.getRoot());
	yo.print();
	ft::RBTIterator<int> iter = yo.find(3);
	std::cout << "RESULTAT DU FIND : " << *iter << std::endl;
	iter--;
	std::cout << "RESULTAT DU FIND : " << *iter << std::endl;
	ft::RBTIterator<int> up = yo.lower_bound(3);
	std::cout << "RESULTAT DU lower : " << *up << std::endl;	
	return 0;
	

};
