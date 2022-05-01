/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 23:54:04 by wluong            #+#    #+#             */
/*   Updated: 2022/05/01 14:59:40 by wluong           ###   ########.fr       */
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

			RBTIterator() : _pnode(), nil() {};

			RBTIterator( Node* n, Node *nill) : _pnode(n), nil(nill){};
			
			RBTIterator(const RBTIterator& other) : _pnode(other._pnode), nil(other.nil) {};

			~RBTIterator() {};



			template <class S>
			RBTIterator &operator=(const RBTIterator<S>& s)
			{
				_pnode = s.get_node();
				this->_node_root = s.get_nil();
				return *this;
			 }

			reference operator*() { return _pnode->_data; };
			
			const reference operator*() const { return _pnode->_data; };

			pointer operator->() { return &(_pnode->_data); };

			const pointer operator->() const { return &(_pnode->_data); };

			RBTIterator&	operator++() {
				Increment();
				return *this;
			};

			RBTIterator&	operator++(int) {
				RBTIterator *tmp = this;
				Increment();
				return *tmp;
			};

			RBTIterator&	operator--() {
				Decrement();
				return *this;
			};

			RBTIterator&	operator--(int) {
				RBTIterator *tmp = this;
				Decrement();
				return *tmp;
			};

			Node *	get_node() const { return _pnode; };

			Node *	get_nil() const { return nil; };

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
//					if (_pnode->_left != tmp)
//						_pnode = tmp;
				}
			}

			void Decrement() {
		//		if (_pnode->_parent->_parent == _pnode && _pnode->_color == red)
		//			_pnode = _pnode->_right;
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
				//	_pnode = parent;
				}
			}

			Node	*_pnode;
			Node	*nil;
			
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

			const_RBTIterator() : _pnode(), nil() {};

			const_RBTIterator( Node* n, Node *nill ) : _pnode(n), nil(nill) {};
			
			const_RBTIterator(const const_RBTIterator& other) : _pnode(other.get_node()) , nil(other.get_nil()) {};

			const_RBTIterator(const iterator& it) : _pnode(it.get_node()), nil(it.get_nil()) {};

			~const_RBTIterator() {};

			template <class S>
			const_RBTIterator &operator=(const const_RBTIterator<S>& s)
			{
				_pnode = s.get_node();
				this->_node_root = s.get_nil();
				return *this;
			 }


			reference operator*() { return _pnode->_data; };
			
			const reference operator*() const { return _pnode->_data; };

			pointer operator->() { return &(_pnode->_data); };

			const pointer operator->() const { return &(_pnode->_data); };

			const_RBTIterator&	operator++() {
				Increment();
				return *this;
			};

			const_RBTIterator&	operator++(int) {
				const_RBTIterator *tmp = this;
				Increment();
				return *tmp;
			};

			const_RBTIterator&	operator--() {
				Decrement();
				return *this;
			};

			const_RBTIterator&	operator--(int) {
				const_RBTIterator *tmp = this;
				Decrement();
				return *tmp;
			};

			Node *	get_node() const { return _pnode; };

			Node *	get_nil() const { return nil; };

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
					while (_pnode == tmp->_right && tmp != nil) {
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
					if (_pnode == parent->_left && parent->_parent != nil) {
						_pnode = parent;
						parent = parent->_parent;
					}
					_pnode = parent;
				}
			}

			Node	*_pnode;
			Node	*nil;
			
	};
};

#endif