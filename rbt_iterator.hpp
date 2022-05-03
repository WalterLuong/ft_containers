/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 23:54:04 by wluong            #+#    #+#             */
/*   Updated: 2022/05/03 06:05:00 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

# include "iterator.hpp"
# include <iostream>

namespace	ft {
	
/***************************************************************************
****************************************************************************
*************						NODES						************
****************************************************************************
***************************************************************************/

	enum Color {red, black};

	template <class T>
	struct node {
	
		public:
			
			node(const T & x = T(), Color c = red) : _left(NULL), _right(NULL), _parent(NULL), _data(x), _color(c) {};
			~node() {};

			node&	operator=(const node & n) {
				this->_left = n._left;
				this->_right = n._right;
				this->_parent = n._parent;
				this->_data = n._data;
				this->_color = n._color;
			};

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

			RBTIterator() : _pnode(), nil(), root() {};

			RBTIterator( Node* n, Node *nill, Node *roott) : _pnode(n), nil(nill), root(roott) {};
			
			RBTIterator(const RBTIterator& other) : _pnode(other._pnode), nil(other.nil), root(other.root) {};

			~RBTIterator() {};



			template <class S>
			RBTIterator &operator=(const RBTIterator<S>& s)
			{
				_pnode = s.get_node();
				nil = s.get_nil();
				root = s.get_root();
				return *this;
			 }

			reference operator*() { return _pnode->_data; };
			
			const reference operator*() const { return _pnode->_data; };

			pointer operator->() { return &(_pnode->_data); };

			const pointer operator->() const { return &(_pnode->_data); };

			RBTIterator&	operator++() {
				if (_pnode == maximum()) {
					_pnode = nil;
					return *this;
				}
				if (_pnode != nil)
					Increment();
				return *this;
			};

			RBTIterator	operator++(int) {
				self tmp(*this);
				if (_pnode == maximum()) {
					_pnode = nil;
					return tmp;
				}
				if (_pnode != nil)
					Increment();
				return tmp;
			};

			RBTIterator&	operator--() {
				if (_pnode == nil) {
					_pnode = maximum();
					return *this;
				}
				Decrement();
				return *this;
			};

			RBTIterator	operator--(int) {
				self tmp(*this);
				if (_pnode == nil) {
					_pnode = maximum();
					return tmp;
				}
				Decrement();
				return tmp;
			};

			Node *	get_node() const { return _pnode; };

			Node *	get_nil() const { return nil; };

			Node *	get_root() const { return root; };

			bool operator==( const RBTIterator& s ) {
				return _pnode == s._pnode;
			};

			bool operator!=( const RBTIterator& s ) {
				return _pnode != s._pnode;
			};

		private:

			void Increment() {
				if (_pnode->_right != nil) {
					_pnode = _pnode->_right;
					while (_pnode->_left != nil) {
						_pnode = _pnode->_left;
					}
				}
				else {
					Node* tmp = _pnode->_parent;
					while (tmp != nil && _pnode == tmp->_right) {
						_pnode = tmp;
						tmp = tmp->_parent;
					}
					if (_pnode->_left != tmp)
						_pnode = tmp;
				}
			}

			void Decrement() {
				if (_pnode->_parent->_parent == _pnode && _pnode->_color == red)
					_pnode = _pnode->_right;
				if (_pnode->_left != nil) {
					_pnode = _pnode->_left;
					while (_pnode->_right != nil) {
						_pnode = _pnode->_right;
					}
				}
				else {
					Node* parent = _pnode->_parent;
					while (parent != nil && _pnode == parent->_left) {
						_pnode = parent;
						parent = parent->_parent;
					}
					_pnode = parent;
				}
			}

			Node	*maximum() {
				Node *tmp = root;
				while (tmp->_right != nil) {
					tmp = tmp->_right;
				}
				return tmp;
				// Node *tmp = _pnode;
				// while (tmp->_parent != nil) {
				// 	tmp = tmp->_parent;
				// }
				// while (tmp->_right != nil) {
				// 	tmp = tmp->_right;
				// }
				// return tmp;
			}

			Node	*_pnode;
			Node	*nil;
			Node	*root;
			
	};

	template <class T>
	class const_RBTIterator {

		public:
			typedef node<T>																			Node;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category		iterator_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef	RBTIterator<T>																	iterator;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T>::reference		reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T>:: pointer		pointer;
			typedef const_RBTIterator<T>															self;

			const_RBTIterator() : _pnode(), nil(), root() {};

			const_RBTIterator( Node* n, Node *nill, Node *roott ) : _pnode(n), nil(nill), root(roott) {};
			
			const_RBTIterator(const const_RBTIterator& other) : _pnode(other.get_node()) , nil(other.get_nil()), root(other.root) {};

			const_RBTIterator(const iterator& it) : _pnode(it.get_node()), nil(it.get_nil()), root(it.get_root()) {};

			~const_RBTIterator() {};

			template <class S>
			const_RBTIterator &operator=(const const_RBTIterator<S>& s)
			{
				_pnode = s.get_node();
				nil = s.get_nil();
				root =s.get_root();
				return *this;
			 }


			reference operator*() { return _pnode->_data; };
			
			const reference operator*() const { return _pnode->_data; };

			pointer operator->() { return &(_pnode->_data); };

			const pointer operator->() const { return &(_pnode->_data); };

			const_RBTIterator&	operator++() {
				if (_pnode == maximum()) {
					_pnode = nil;
					return *this;
				}
				if (_pnode != nil)
					Increment();
				return *this;
			};

			const_RBTIterator	operator++(int) {
				self tmp(*this);
				if (_pnode == maximum()) {
					_pnode = nil;
					return tmp;
				}
				if (_pnode != nil)
					Increment();
				return tmp;
			};

			const_RBTIterator&	operator--() {
				if (_pnode == nil) {
					_pnode = maximum();
					return *this;
				}
				Decrement();
				return *this;
			};

			const_RBTIterator	operator--(int) {
				self tmp(*this);
				if (_pnode == nil) {
					_pnode = maximum();
					return tmp;
				}
				Decrement();
				return tmp;
			};

			Node *	get_node() const { return _pnode; };

			Node *	get_nil() const { return nil; };

			Node *	get_root() const { return root; };

			bool operator==( const const_RBTIterator& s ) {
				return _pnode == s._pnode;
			};

			bool operator!=( const const_RBTIterator& s ) {
				return _pnode != s._pnode;
			};

		private:

			void Increment() {
				if (_pnode->_right != nil) {
					_pnode = _pnode->_right;
					while (_pnode->_left != nil) {
						_pnode = _pnode->_left;
					}
				}
				else {
					Node* tmp = _pnode->_parent;
					while (tmp != nil && _pnode == tmp->_right) {
						_pnode = tmp;
						tmp = tmp->_parent;
					}
					if (_pnode->_left != tmp)
						_pnode = tmp;
				}
			}

			void Decrement() {
				if (_pnode->_parent->_parent == _pnode && _pnode->_color == red)
					_pnode = _pnode->_right;
				if (_pnode->_left != nil) {
					_pnode = _pnode->_left;
					while (_pnode->_right != nil) {
						_pnode = _pnode->_right;
					}
				}
				else {
					Node* parent = _pnode->_parent;
					while (parent != nil && _pnode == parent->_left) {
						_pnode = parent;
						parent = parent->_parent;
					}
					_pnode = parent;
				}
			}

			Node	*maximum() {
				Node *tmp = root;
				while (tmp->_right != nil) {
					tmp = tmp->_right;
				}
				return tmp;
			}

			// Node	*maximum() {
			// 	Node *tmp = _pnode;
			// 	while (tmp->_parent != nil) {
			// 		tmp = tmp->_parent;
			// 	}
			// 	while (tmp->_right != nil) {
			// 		tmp = tmp->_right;
			// 	}
			// 	return tmp;
			// }

			Node	*_pnode;
			Node	*nil;
			Node	*root;
			
	};
};

#endif