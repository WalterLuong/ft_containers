/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 07:19:59 by wluong            #+#    #+#             */
/*   Updated: 2022/04/12 06:56:49 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include "rbt_iterator.hpp"
# include "pair.hpp"
# include <algorithm>
# include <memory>
# include <cstddef>

namespace ft {

/***************************************************************************
****************************************************************************
*************					RED BLACK TREE					************
****************************************************************************
***************************************************************************/

	template < class T, class Node = node<T>, class Allocator = std::allocator<Node>>
	class RedBlackTree {

		public:
		
			typedef T										value_type;
			// typedef node<T>									Node;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef typename Allocator::size_type			size_type;
			typedef ft::RBTIterator<T>						iterator;
			typedef ft::RBTIterator<const T>				const_iterator;
			typedef ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;
		
		public:

/***************************************************************************
****************************************************************************
*************					CONSTRUCTEURS					************
****************************************************************************
***************************************************************************/

		RedBlackTree( const Allocator& alloc = Allocator()) : _alloc(alloc), _size(0) {
			nil = _alloc.allocate(1);
			_alloc.construct(nil, Node());
			nil->_color = black;
			nil->_left = nil;
			nil->_right = nil;
			nil->_parent = nil;
			root = nil;
		};
		
		~RedBlackTree() {};

/***************************************************************************
****************************************************************************
*************					RBT FONCTIONS					************
****************************************************************************
***************************************************************************/

		void	_delete( Node *z ) {
			Node *y;
			Node *x;
			y = z;
			Color original = y->_color;
			if (z->_left == nil) {
				x = z->_right;
				transplant(z, z->_right);
			}
			else if (z->_right == nil) {
				x = z->_left;
				transplant(z, z->_left);
			}
			else {
				y = minimum(z->_right);
				original = y->_color;
				x = y->_right;
				if (y->_parent == z) {
					x->_parent = y;
				}
				else {
					transplant(y, y->_right);
					y->_right = z->_right;
					y->_right->_parent = y;
				}
				transplant(z, y);
				y->_left = z->_left;
				y->_left->_parent = y;
				y->_color = z->_color;
			}
			if (original == black)
				_deleteFixup(x);
			destroy_node(z);
		};

		void	insert(const value_type& x) {

			Node *z = new_node(x);
			Node *y = nil;
			Node *u = root;

			if (root == nil) {
				z->_color = black;
				root = z;
				return ;
			}
			while (u != nil) {
				y = u;
				if (z->_data < u->_data)
					u = u->_left;
				else
					u = u->_right;
			}
			z->_parent = y;
			if (y == nil) {
				root = z;
			}
			else if (z->_data < y->_data) {
				y->_left = z;
			}
			else {
				y->_right = z;
			}
			insert_fixup(z);
		};



/***************************************************************************
****************************************************************************
*************					ITERATORS						************
****************************************************************************
***************************************************************************/

		iterator begin() {
			Node *tmp = root;
			while (tmp->_left != nil) {
				tmp = tmp->_left;
			}
			return iterator(tmp, nil);
		};

		const_iterator begin() const {
				Node *tmp = root;
			while (tmp->_left != nil) {
				tmp = tmp->_left;
			}
			return const_iterator(tmp, nil);
		};

		iterator end() {
			return iterator(nil, nil);
		};

		// const_iterator end() const {
		// 	return const_iterator(nil);
		// };

		// reverse_iterator rbegin() {

		// };

		// const_reverse_iterator rbegin() const {

		// };

		// reverse_iterator rend() {

		// };

		// const_reverse_iterator rend() const {

		// };


/***************************************************************************
****************************************************************************
*************					GETTER							************
****************************************************************************
***************************************************************************/

		Node *	getRoot() { return root; };


		void _InOrder(Node *z)
		{
			if (z != nil)
			{
				_InOrder(z->_left);
				std::cout << "<" << z->_data << ">"<< std::endl;
				_InOrder(z->_right);
				}
		}
/***************************************************************************
****************************************************************************
*************					MAP FONCTIONS					************
***************************************************************************/
		// pair<iterator, bool> insert(const value_type& x);

		// RBT
		// iterator insert(iterator position, const value_type& x);

		// RBT
		// template <class InputIterator>
		// void insert(InputIterator first, InputIterator last);


		// MAP
		// void erase(iterator position);


		// MAP
		// size_type erase(const key_type& x);

		// RBT
		// void erase(iterator first, iterator last);

		// MAP
		// void swap(map<Key,T,Compare,Allocator>&);


		// RBT
		// void clear() {
			
		// };

		// MAP
		// key_compare key_comp() const;


		// MAP
		// value_compare value_comp() const;

		// RBT
		// iterator find(const key_type& x) {
		// 	Node *tmp = root;
		// 	if (tmp != nil) {
		// 		while (tmp != nil) {
		// 			if (tmp->_data)
		// 		}
		// 	}
		// };


		/* MAP */
		// const_iterator find(const key_type& x) const;

		// size_type count(const key_type& x) const;

		// iterator lower_bound(const key_type& x);

		// pair<iterator,iterator>
		// equal_range(const key_type& x);

		// pair<const_iterator,const_iterator>
		// equal_range(const key_type& x) const;

		private:
		
/***************************************************************************
****************************************************************************
*************					RBT FONCTIONS					************
****************************************************************************
***************************************************************************/

		void	left_rotate(Node *x) {
			Node *y;
			y = x->_right;
			if (y->_left != nil) {
				y->_left = x;
			}
			y->_parent = x->_parent;
			if (x->_parent == nil) {
				x->_parent->_right = y;
			}
			y->_left = x;
			x->_parent = y;
			
			// Node *y = x->_right;
			// x->_right = y->_left;
			// if (y->_left != nil) {
			// 	y->_left->_parent = x;
			// }
			// y->_parent = x->_parent;
			// if (x->_parent == nil) {
			// 	root = y;
			// }
			// else if (x == x->_parent->_left) {
			// 	x->_parent->_left = y;
			// }
			// else {
			// 	x->_parent->_right = y;
			// }
			// y->_left = x;
			// x->_parent = y;
		};

		void	right_rotate(Node *x) {
			// Node *y;
			// y = x->_left;
			// if (y->_right != nil) {
			// 	y->_right = x;
			// }
			// y->_parent = x->_parent;
			// if (x->_parent == nil) {
			// 	root = y;
			// }
			// else if (x == x->_parent->_right) {
			// 	x->_parent->_right = y;
			// }
			// else {
			// 	x->_parent->_left = y;
			// }
			// y->_right = x;
			// x->_parent = y;
			
			Node *y = x->_left;
			x->_left = y->_right;
			if (y->_right != nil) {
				y->_right->_parent = x;
			}
			y->_parent = x->_parent;
			if (x->_parent == nil) {
				root = y;
			}
			else if (x == x->_parent->_right) {
				x->_parent->_right = y;
			}
			else {
				x->_parent->_left = y;
			}
			y->_right = x;
			x->_parent = y;
		};

		void	insert_fixup(Node *z) {
			Node *y;

			while (z->_parent->_color == red) {
				if (z->_parent == z->_parent->_parent->_right) {
					y = z->_parent->_parent->_left;
					if (y->_color == red) {
						y->_color = black;
						z->_parent->_color = black;
						z->_parent->_parent->_color = red;
						z = z->_parent->_parent;
					}
					else {
						if (z == z->_parent->_left) {
							z = z->_parent;
							right_rotate(z);
						}
						z->_parent->_color = black;
						z->_parent->_parent->_color = red;
						left_rotate(z->_parent->_parent);
					}
				}
				else {
					y = z->_parent->_parent->_right;
					if (y->_color == red) {
						z->_parent->_color = black;
						y->_color = black;
						z->_parent->_parent->_color = red;
						z = z->_parent->_parent;
					}
					else {
						if (z == z->_parent->_right) {
							z = z->_parent;
							left_rotate(z);
						}
						z->_parent->_color = black;
						z->_parent->_parent->_color = red;
						left_rotate(z->_parent->_parent);
					}
				}
				if (z == root)
					break;
			}
			root->_color = black;
		};

		void	transplant(Node *u, Node *v) {
			if (u->_parent == nil)
				root = v;
			else if (u == u->_parent->_left)
				u->_parent->_left = v;
			else
				u->_parent->_right =v;
			v->_parent = u->_parent;
		};

		Node	*minimum(Node *x) {
			while (x->_left != nil) {
				x = x->_left;
			}
			return x;
		};

		void	_deleteFixup( Node *x ) {
			Node *tmp;

			while (x != root && x->_color == black) {
				if (x == x->_parent->_left) {
					tmp = x->_parent->_right;
					if (tmp->_color == red) {
						tmp->_color = black;
						x->_parent->_color = red;
						left_rotate(x->_parent);
						tmp = x->_parent->_right;
					}
					if (tmp->_left->_color == black && tmp->_right->_color == black) {
						tmp->_color = red;
						x = x->_parent;
					}
					else {
						if (tmp->_right->_color == black) {
							tmp->_left->_color = black;
							tmp->_color = red;
							right_rotate(tmp);
							tmp = x->_parent->_right;
						}
						tmp->_color = x->_parent->_color;
						x->_parent->_color = black;
						tmp->_right->_color = black;
						left_rotate(x->_parent);
						x = root;
					}
				}
				else if (x == x->_parent->_right) {
					tmp = x->_parent->_left;
					if (tmp->_color == red) {
						tmp->_color = black;
						x->_parent->_color = red;
						right_rotate(x->_parent);
						tmp = x->_parent->_left;
					}
					if (tmp->_right->_color == black && tmp->_left->_color == black) {
						tmp->_color = red;
						x = x->_parent;
					}
					else {
						if (tmp->_left->_color == black) {
							tmp->_right->_color = black;
							tmp->_color = red;
							left_rotate(tmp);
							tmp = x->_parent->_left;
						}
						tmp->_color = x->_parent->_color;
						x->_parent->_color = black;
						tmp->_left->_color = black;
						right_rotate(x->_parent);
						x = root;
					}
				}
			}
			x->_color = black;
		}


/***************************************************************************
****************************************************************************
*************					NODES FUNCTIONS					************
****************************************************************************
***************************************************************************/

		Node	*new_node(const value_type& x) {
			Node *newNode;
	
			newNode = _alloc.allocate(1);
			this->_alloc.construct(newNode, Node(x));
			newNode->_color = red;
			newNode->_left = nil;
			newNode->_right = nil;
			newNode->_parent = nil;
			_size++;
			return newNode;
		};

		void	destroy_node(Node *x) {
			this->_alloc.destroy(x);
			_alloc.deallocate(x, 1);
		};

		Node			*root;
		Node			*nil;
		Allocator		_alloc;
		size_type		_size;

	};

}

#endif