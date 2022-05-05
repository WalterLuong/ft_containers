/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 07:19:59 by wluong            #+#    #+#             */
/*   Updated: 2022/05/05 07:13:37 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include "rbt_iterator.hpp"
# include "pair.hpp"
# include <algorithm>
# include <memory>
# include <cstddef>
# include <iomanip>
# include <iostream>
# include <utility>
# include <string>
# include <sstream>
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft {

/***************************************************************************
****************************************************************************
*************					RED BLACK TREE					************
****************************************************************************
***************************************************************************/

	template < class T, class Compare, class Node = node<T>, class Allocator = std::allocator<Node> >
	class RedBlackTree {

		public:
		
			typedef T										value_type;
			typedef Compare									compare;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef typename Allocator::size_type			size_type;
			typedef ft::RBTIterator<T>						iterator;
			typedef ft::const_RBTIterator<T>				const_iterator;
			typedef ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		
		public:

/***************************************************************************
****************************************************************************
*************					CONSTRUCTEURS					************
****************************************************************************
***************************************************************************/

		RedBlackTree( const compare& cmp = compare(), const Allocator& alloc = Allocator() ) : _alloc(alloc), _size(0), _cmp(cmp) {
			nil = _alloc.allocate(1);
			_alloc.construct(nil, Node());
			nil->_color = black;
			nil->_left = nil;
			nil->_right = nil;
			nil->_parent = nil;
			root = nil;
		};
		
		~RedBlackTree() {
			clear();
			destroy_node(nil);
		};

/***************************************************************************
****************************************************************************
*************					RBT FONCTIONS					************
****************************************************************************
***************************************************************************/

		size_type	erase( const value_type& del ) {
			iterator it = find(del);
			Node *z = it.get_node();
			Node *y;
			Node *x;
			y = z;
			Color original = y->_color;
			if (z == nil) {
				return 0;
			}
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
			return 1;
		};

		Node	*insert(const value_type& x) {

			iterator it = find(x);
			if (it.get_node() != nil) {
				return it.get_node();
			}
			Node *z = new_node(x);
			Node *y = nil;
			Node *u = root;
			if (root == nil) {
				z->_color = black;
				root = z;
				return z;
			}
			while (u != nil) {
				y = u;
				if (_cmp(z->_data, u->_data)  /*z->_data < u->_data*/)
					u = u->_left;
				else
					u = u->_right;
			}
			z->_parent = y;
			if (y == nil) {
				root = z;
			}
			else if (_cmp(z->_data, y->_data) /* z->_data < y->_data*/) {
				y->_left = z;
			}
			else {
				y->_right = z;
			}
			insert_fixup(z);
			return z;
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
			return iterator(tmp, nil, root);
		};

		const_iterator begin() const {
			Node *tmp = root;
			while (tmp->_left != nil) {
				tmp = tmp->_left;
			}
			return const_iterator(tmp, nil, root);
		};

		iterator end() {
			return iterator(nil, nil, root);
		};

		const_iterator end() const {
			return const_iterator(nil, nil, root);
		};

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		};

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(rend());
		};

		reverse_iterator rend() {
			return reverse_iterator(begin());
		};

		const_reverse_iterator rend() const {
			return const_reverse_iterator(rend());
		};


/***************************************************************************
****************************************************************************
*************					GETTER							************
****************************************************************************
***************************************************************************/

		Node * getRoot() { return root; };

		Node * getNil() { return nil; };

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

		void clear() {
			Node *tmp = root;
			while (tmp != nil) {
				_clear_helper(tmp->_data);
				tmp = root;
			}
		};

		iterator find(const value_type& x) {
			Node *tmp = root;
			if (tmp != nil) {
				while (tmp != nil) {
					if (!_cmp(tmp->_data, x) && !_cmp(x, tmp->_data))
						return iterator(tmp, nil, root);
					else if (_cmp(x, tmp->_data)) {
						tmp = tmp->_left;
					}
					else {
						tmp = tmp->_right;
					}
				}
			}
			return end();
		};

		const_iterator find(const value_type& x) const {
			Node *tmp = root;
			if (tmp != nil) {
				while (tmp != nil) {
					if (!_cmp(tmp->_data, x) && !_cmp(x, tmp->_data))
						return const_iterator(tmp, nil, root);
					else if (_cmp(x, tmp->_data)) {
						tmp = tmp->_left;
					}
					else {
						tmp = tmp->_right;
					}
				}
			}
			return end();
		};

		bool empty() const {
			return _size == 0 ? 1 : 0;
		};

		size_type	size(void) const { return _size; };

		size_type max_size() const { return _alloc.max_size(); } ;

		size_type count(const value_type& x) const {
			const_iterator it = find(x);
			if (it == end()) {
				return 0;
			}
			return 1;
		};

		iterator lower_bound(const value_type& x) {
			iterator it = begin();
			if (_cmp(x,*it))
				return it;
			it = find(x);
			return it;
		};

		const_iterator lower_bound(const value_type& x) const {
			const_iterator it = begin();
			if (_cmp(x,*it))
				return it;
			it = find(x);
			return it;
		};
		
		iterator upper_bound(const value_type& x) {
			// iterator it = begin();
			// if (_cmp(x,*it))
			// 	return it;
			// it = find(x);
			// it--;
			// return it;
			iterator	ite = end();
			iterator	it = lower_bound(x);

			if (it != ite && !_cmp(x,*it) && !_cmp(*it, x))
				return (++it);
			return (it);
		};
		
		const_iterator upper_bound(const value_type& x) const {
			// const_iterator it = begin();
			// if (_cmp(x,*it))
			// 	return it;
			// it = find(x);
			// it++;
			// return it;
			const_iterator	ite = end();
			const_iterator	it = lower_bound(x);

			if (it != ite && !_cmp(x,*it) && !_cmp(*it, x))
				return (++it);
			return (it);
		};

		void	print(void)
		{
			std::stringstream	buffer;

			std::cout << "size: " << this->size() << std::endl;
			if (root != nil)
			{
				_print(root, buffer, true, "");
				std::cout << buffer.str();
			}
		};


		void swap(RedBlackTree& other) {
			std::swap(root, other.root);
			std::swap(nil, other.nil);
			std::swap(_cmp, other._cmp);
			std::swap(_size, other._size);
		};

		private:
		
/***************************************************************************
****************************************************************************
*************					RBT FONCTIONS					************
****************************************************************************
***************************************************************************/

		void	left_rotate(Node *x) {
			Node *y = x->_right;
			x->_right = y->_left;
			if (y->_left != nil) {
				y->_left->_parent = x;
			}
			y->_parent = x->_parent;
			if (x->_parent == nil) {
				root = y;
			}
			else if (x == x->_parent->_left) {
				x->_parent->_left = y;
			}
			else {
				x->_parent->_right = y;
			}
			y->_left = x;
			x->_parent = y;
		};

		void	right_rotate(Node *x) {
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
						y->_color = black;
						z->_parent->_color = black;
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
						right_rotate(z->_parent->_parent);
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
			Node *tmp = x;
			while (tmp->_left != nil) {
				tmp = tmp->_left;
			}
			return tmp;
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
		};

		void	_clear_helper( const value_type& del ) {
			iterator it = find(del);
			Node *z = it.get_node();
			Node *y;
			Node *x;
			y = z;
			Color original = y->_color;
			if (z == nil) {
				return ;
			}
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
			destroy_node(z);
		};

		void	_print(Node * node, std::stringstream &buffer, bool isTail, std::string prefix)
		{
			if (node->_right != nil)
				_print(node->_right, buffer, false, std::string(prefix).append(isTail ? "│   " : "    "));
			buffer << prefix << (isTail ? "└── " : "┌── ");
			if (node->_color == red)
				buffer << "\033[31m";
			buffer << node->_data << "\033[0m" << std::endl;
			if (node->_left != nil)
				_print(node->_left, buffer, true, std::string(prefix).append(isTail ? "    " : "│   "));
		};

/***************************************************************************
****************************************************************************
*************			 		NODES FUNCTIONS					************
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
			_size--;
		};

		Node			*root;
		Node			*nil;
		Allocator		_alloc;
		size_type		_size;
		compare			_cmp;

	};

}

#endif