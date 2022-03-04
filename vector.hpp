/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 00:53:43 by wluong            #+#    #+#             */
/*   Updated: 2022/03/04 06:27:11 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"

namespace	ft {

	template < class T, class Allocator = std::allocator<T> >
	class vector {

		public :

		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef ft::random_access_iterator<T>			iterator;
		typedef ft::random_access_iterator<const T>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


		/*===============================================*
		*			CONSTRUCTORS & DESTRUCTORS			 *
		*===============================================*/
	
		explicit vector( const Allocator& alloc = Allocator() ) : _pointer(0), _alloc(alloc), _capacity(0), _size(0) {};

		explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator() ) : _pointer(0), _alloc(alloc), _capacity(count), _size(count) {
			_pointer = _alloc.allocate(count);
			for (size_type i(0); i < count; i++) {
				_alloc.construct(_pointer + i, value);
			}
		};
		
		template <class InputIterator>
		vector( InputIterator first, InputIterator last, const Allocator& alloc = Allocator() ) : _alloc(alloc) {
			InputIterator copy;
			size_type	size;
			size_type	i;
			copy = first;
			i = 0;
			size = 0;
			while (copy != last) {
				copy++;
				size++;
			}
			_pointer = _alloc.allocate(size);
			_size = size;
			_capacity = size;
			while (first != last) {
				_alloc.construct(_pointer + i, *first);
				first++;
			}
		};
		
		vector(const vector<T,Allocator>& x) : _alloc(x._alloc) {
			_pointer = _alloc.allocate(x._size);
			for (size_type i(0); i < x._size; i++) {
				_alloc.construct(_pointer + i, *(x._pointer + i));
			}
			_size = x._size;
			_capacity = x._capacity;
		};

		vector<T, Allocator>& operator=(const vector< T, Allocator >& x) {
			this->clear();
			_alloc.deallocate(_pointer, _capacity);
			_alloc = x._alloc;
			_pointer = _alloc.allocate(x._size);
			for (size_type i(0); i < x._size; i++) {
				_alloc.construct(_pointer + i, *(x._pointer + i));
			}
			_size = x._size;
			_capacity = x._capacity;
			return *this;
		};

		
		~vector() {
			clear();
			_alloc.deallocate(_pointer, _capacity);
		};
		
		template <class InputIterator>
		void assign( InputIterator first, InputIterator last ) {
			erase(begin(), end());
			insert(begin(), first, last);
		};
		
		void assign( size_type n, const T& u ) {
			erase(begin(), end());
			insert(begin(), n, u);
		};
		
		allocator_type get_allocator() const {
			return _alloc;
		}

		/*===============================================*
		*					ITERATORS					 *
		*===============================================*/

		iterator begin() { return iterator(_pointer); };

		const_iterator begin() const { return const_iterator(_pointer); };

		iterator end() { return iterator(_pointer + _size); };

		const_iterator end() const { return const_iterator(_pointer + _size); };

		reverse_iterator rbegin() { return reverse_iterator(iterator(_pointer + _size)); };

		const_reverse_iterator rbegin() const { return const_reverse_iterator(const_iteraotr(_pointer + _size)); };

		reverse_iterator rend() { return reverse_iterator(iterator(_pointer)); };
		
		const_reverse_iterator rend() const { return const_reverse_iterator(const_iterator(_pointer)); };

		/*===============================================*
		*					CAPACITY					 *
		*===============================================*/

		size_type size() const { return _size; };

		size_type max_size() const { return _alloc.max_size(); };

		void resize(size_type sz, T c = T()) {
			if (sz > size())
				insert(end(), sz - size(), c);
			else if (sz < size())
				erase(begin() + sz, end());
			else
				return ;
		};
		
		size_type capacity() const { return _capacity; };
		
		bool empty() const { return (_size == 0); };
		
		void reserve(size_type n) {
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			else if (n <= capacity())
				return;
			else {
				pointer	tmp;
				tmp = _alloc.allocate(n);
				for (size_type i(0); i < _size; i++) {
					_alloc.construct(tmp + i, *(_pointer + i));
				}
				_alloc.deallocate(_pointer, _capacity);
				_capacity = n;
				_pointer = tmp;
			}
		};
		
		/*===============================================*
		*				ELEMENT ACCESS					 *
		*===============================================*/

		reference operator[]( size_type n ) {
			return *(this->begin() + n);
		};

		const_reference operator[]( size_type n ) const {
			return *(this->begin() + n);
		};

		const_reference at( size_type n ) const {	
			if (n < _size)
				return *(this->begin() + n);
			else
				throw std::out_of_range("out_of_range exception!");
		};

		reference at( size_type n ) {
			if (n < _size)
				return *(this->begin() + n);
			else
				throw std::out_of_range("out_of_range exception!");
		}

		reference front() {
			return *this->begin();
		};

		const_reference front() const {
			return *this->begin();
		};

		reference back() {
			return *--this->end();
		};

		const_reference back() const {
			return *--this->end();
		};

		/*===============================================*
		*				MODIFIERS						 *
		*===============================================*/

		void push_back( const T& x ) {
			if (_capacity == 0) {
				reserve(1);
			}
			else if (_size == _capacity && _capacity != 0) {
				reserve(2 * _capacity);
			}
			_alloc.construct(_pointer + _size, x);
			_size++;
		};

		void pop_back() {
			_alloc.destroy(&this->back());
			_size--;
		};

		iterator insert( iterator position, const T& x ) {
			size_type distance;
			distance = position - this->begin();
			if (_capacity == 0) {
				reserve(1);
			}
			else if (_capacity == _size) {
				reserve(2 * _capacity);
			}
			_alloc.construct(_pointer + _size, _pointer[_size - 1]);
			_size++;
			for (size_type j(_size - 2); j > distance; j--) {
				_pointer[j] = _pointer[j - 1];
			}
			_pointer[distance] = x;
			return this->begin() + distance;
		};

		void insert( iterator position, size_type n, const T& x ) {
			size_type distance;
			distance = position - this->begin();
			if (_capacity == 0) {
				reserve(1);
			}
			else if (_capacity == _size) {
				while (_capacity < _size + n) {
					reserve(2 * _capacity);
				}
			}
			for (size_type i(0); i < n; i++) {
				_alloc.construct(_pointer + _size, _pointer[_size - 1]);
				_size++;
			}
			for (size_type j(0); j < n; j++) {
				_pointer[j + n] = x;
			}
		};

		template <class InputIterator>
		void insert( iterator position, InputIterator first, InputIterator last ) {
			size_type distance;
			size_type it_dist;
			it_dist = last - first;
			distance = position - this->begin();
			if (_capacity == 0) {
				reserve(1);
			}
			else if (_capacity == _size) {
				while (_capacity < _size + it_dist) {
					reserve(2 * _capacity);
				}
			}
			for (size_type i(0); i < it_dist; i++) {
				_alloc.construct(_pointer + _size, _pointer[_size - 1]);
				_size++;
			}
			for (size_type j(0); j < it_dist; j++) {
				_alloc.construct(&_pointer[j + distance], *first);
				first++;
			}
		};

		iterator erase( iterator position ) {
			size_type	distance;
			size_type	i;
			iterator	it;
			i = 0;
			it = this->begin();
			distance = position - it;
			i = distance;
			while (it + distance != this->end() - 1) {
				i++;
				_pointer[i - 1] = _pointer[i];
				it++;	
			}
			this->pop_back();
			return this->begin() + distance;
		};

		iterator erase( iterator first, iterator last ) {
			size_type	i;
			iterator	it;
			i = 0;
			it = this->begin();
			while (it != first) {
				i++;
				it++;
			}
			while (first != last) {
				erase(it);
				++first;
			}
			return this->begin() + i;
		};

		// void swap( vector<T,Allocator>& );

		void clear() {
			for (size_type i(0); i < _size; i++) {
				_alloc.destroy(_pointer + i);
			}
			_size = 0;
		};

		private:

		pointer				_pointer;
		allocator_type		_alloc;
		size_type			_capacity;
		size_type			_size;
	};

	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	
}