/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 07:19:59 by wluong            #+#    #+#             */
/*   Updated: 2022/03/29 00:22:39 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include "iterator.hpp"
# include <iostream>
# include <algorithm>
# include <memory>
# include <cstddef>

namespace ft {

	enum Color {red, black};

	template <class T>
	struct node {
	
		public:
			node(const T & x = T(), Color c = red) : _left(nullptr), _right(nullptr), _parent(nullptr), _data(x), _color(c) {};

		private:
			node<T>		*_left;
			node<T>		*_right;
			node<T>		*_parent;
			T			_data;
			Color		_color;
	};

	template <class T>
	class RBTIterator {

		public:
			typedef node<T>																			Node;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category		iterator_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>:: pointer				pointer;
			typedef RBTIterator<T>																	self;

			RBTIterator( Node* n=nullptr) : _pnode(n) {};

			reference operator*() { return _pnode->_data; };

			pointer operator->() { return &(_pnode->_data); };

			self&	operator++() {
				Increment();
				return *this;
			};

			self&	operator++(int) {
				self tmp = this;
				Increment();
				return tmp;
			};

			self&	operator--() {
				Decrement();
				return *this;
			};

			self&	operator--(int) {
				self tmp = this;
				Decrement();
				return *tmp;
			};

			bool operator==( const self& s ) {
				return _pnode == s._pnode;
			};

			bool operator!=( const self& s ) {
				return _pnode != s._pnode;
			};

		private:

			void Increment() {
				if (_pnode->_right) {
					Node* tmp = _pnode->_right;
					while (tmp->_left) {
						tmp = tmp->_left;
					}
					_pnode = tmp;
				}
				else {
					Node* tmp = _pnode->_parent;
					if (tmp->_right==_pnode) {
						while (_pnode == tmp->_right) {
							_pnode = tmp;
							tmp = tmp->_parent;
						}
						
					}
					if (_pnode->_right != tmp)
						_pnode = tmp;
				}
			}

			void Decrement() {
				if (_pnode->_parent->_parent == _pnode && _pnode->_color = red)
					_pnode = _pnode->_left;
				else if (_pnode->_left) {
					while (_pnode->_right) {
						_pnode = _pnode->_right;
					}
				}
				else {
					Node* parent = _pnode->_parent;
					while (parent->_left == _pnode) {
						_pnode = parent;
						parent = parent->_parent;
					}
					_pnode = parent;
				}
			}

			Node	_pnode;
			
	};

	template < class T, class Allocator = std::allocator, class Compare >
	class RedBlackTree {

		typedef T									value_type;
		typedef Compare								value_compare;
		typedef node<T>								Node;
		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef typename Allocator::size_type		size_type;

		public:

		RedBlackTree() {
			nil->_color = black;
			nil->_data = NULL;
			nil->_left = NULL;
			nil->_right = NULL;
			nil->_parent = NULL;

		};
		RedBlackTree() {};
		RedBlackTree() {};
		~RedBlackTree() {};

		insert(Node z) {
			Node y = nil;
			Node x = root;

			while (x != nil) {
				y = x;
				if (z._data < x._data)
					x = x._left;
				else
					x = x._right;
			}
			z._parent = y;
			if (y == nil) {
				root = z;
			}
			else if (z._data < y._data)
				y._left = z;
			else
				y._right = z;
			z._left = nil;
			z._right = nil;
			z._color = red;
			insert_fixup();
		};

		private:
		
		left_rotate(Node x) {
			Node y;
			y = x._right;
			if (y._left != nil) {
				y._left = x;
			}
			y._parent = x._parent;
			if (x._parent == nil) {
				root = y;
			}
			else if (x == x._parent->_left) {
				x._parent->_left = y;
			}
			else {
				x._parent->_right = y;
			}
			y._left = x;
			x._parent = y;
		};

		insert_fixup(Node z) {
			Node y;

			while (z._parent->_color == red) {
				if (z._parent == z._parent->_parent->_left) {
					y = z._parent->_parent->_right;
					if (y._color == red) {
						z._parent->_color = black;
						y._color = black;
						z._parent->_parent->_color = red;
						z = z._parent->_parent;
					}
					else {
						if (z == z._parent->_right) {
							z = z._parent;
							left_rotate(z);
						}
					}
					z._parent->_color = black;
					z._parent->_parent->_color = red;
					right_rotate(z);
				}
				else {
					y = z._parent->_parent->_left;
					if (y._color == red) {
						z._parent->_color = black;
						y._color = black;
						z._parent->_parent->_color = red;
						z = z._parent->_parent;
					}
					else {
						if (z == z._parent->_left) {
							z = z._parent;
							right_rotate(z);
						}
					}
					z._parent->_color = black;
					z._parent->_parent->_color = red;
					left_rotate(z);
				}
			}
		}

		Node	*root;
		Node	*nil;

	};

}

#endif