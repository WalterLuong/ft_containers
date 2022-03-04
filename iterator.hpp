/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 07:00:59 by wluong            #+#    #+#             */
/*   Updated: 2022/03/02 02:24:44 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iostream>
#include <limits>
#include <typeinfo>
#include <cstddef>


namespace ft {

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	template <class Iterator>
	struct iterator_traits
	{

			typedef typename Iterator::difference_type				difference_type;
			typedef typename Iterator::value_type					value_type;
			typedef typename Iterator::pointer						pointer;
			typedef typename Iterator::reference					reference;
			typedef typename Iterator::iterator_type				iterator_category;

	};

	template <class T>
	struct iterator_traits<T*>
	{

			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::random_access_iterator_tag	iterator_category;

	};

	template <class T>
	struct iterator_traits<const T*>
	{

			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef const T*								pointer;
			typedef const T&								reference;
			typedef ft::random_access_iterator_tag	iterator_category;

	};



	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {

			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;

	};



	/************************************************************
	*															*
	*				RANDOM ACCESS ITERATOR						*
	*															*
	************************************************************/

	template <class T>
	class random_access_iterator
	{

		public:

			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category			iterator_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>:: pointer			pointer;

			random_access_iterator() : _current(0) {};

			explicit random_access_iterator(pointer x) : _current(x) {};

			template <class U>
			random_access_iterator(const random_access_iterator<U> &u) : _current(u.base()) {};

			pointer base() const {
				return _current;
			};

			reference operator*() const {
				return *_current;
			};

			pointer operator->() const {
				return &(operator*());
			};

			template <class U>
			random_access_iterator& operator=(const random_access_iterator<U> &u) {
				_current = u.base();
				return *this;
			};

			random_access_iterator& operator++() {
				++_current;
				return *this;
			};

			random_access_iterator operator++(int) {
				random_access_iterator tmp = *this;
				++_current;
				return tmp;
			};

			random_access_iterator& operator--() {
				--_current;
				return *this;
			};

			random_access_iterator operator--(int) {
				random_access_iterator tmp = *this;
				--_current;
				return tmp;
			};

			random_access_iterator operator+(difference_type n) const {
				random_access_iterator tmp(*this);
				return (tmp += n);
			};

			random_access_iterator& operator+=(difference_type n) {
				_current += n;
				return *this;
			};

			random_access_iterator operator-(difference_type n) const {
				random_access_iterator tmp(*this);
				return (tmp -= n);
			};

			random_access_iterator& operator-=(difference_type n) {
				_current -= n;
				return *this;
			};

			reference operator[](difference_type n) const {
				return *(_current + n);
			};

			protected:

				pointer _current;
	};

	template <class T1, class T2>
	bool operator==( const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {
		return x.base() == y.base();
	};

	template <class T>
	bool operator==( const random_access_iterator<T>& x, const random_access_iterator<T>& y) {
		return x.base() == y.base();
	};

	template <class T1, class T2>
	bool operator<( const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {
		return x.base() < y.base();
	};

	template <class T>
	bool operator<( const random_access_iterator<T>& x, const random_access_iterator<T>& y) {
		return x.base() < y.base();
	};

	template <class T1, class T2>
	bool operator!=(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {
		return x.base() != y.base();
	};

	template <class T>
	bool operator!=(const random_access_iterator<T>& x, const random_access_iterator<T>& y) {
		return x.base() != y.base();
	};

	template <class T1, class T2>
	bool operator>(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {
		return x.base() > y.base();
	};
	
	template <class T>
	bool operator>(const random_access_iterator<T>& x, const random_access_iterator<T>& y) {
		return x.base() > y.base();
	};

	template <class T1, class T2>
	bool operator>=(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {
		return x.base() >= y.base();
	};

	template <class T>
	bool operator>=(const random_access_iterator<T>& x, const random_access_iterator<T>& y) {
		return x.base() >= y.base();
	};
	
	template <class T1, class T2>
	bool operator<=(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {
		return x.base() <= y.base();
	};
	
	template <class T>
	bool operator<=(const random_access_iterator<T>& x, const random_access_iterator<T>& y) {
		return x.base() <= y.base();
	};

	template <class T1, class T2>
	typename random_access_iterator<T1>::difference_type operator-(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {
		return x.base() - y.base();
	};
	
	template <class T>
	typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T>& x, const random_access_iterator<T>& y) {
		return x.base() - y.base();
	};

	template <class T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& x) {
		return random_access_iterator<T> (x.base() + n);
	};

	template <class Iterator>
	class reverse_iterator
	{

		public:

			typedef Iterator	iterator_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;

			reverse_iterator() : current() {};

			explicit reverse_iterator(Iterator x) : current(x) {};

			template <class U>
			reverse_iterator(const reverse_iterator<U> &u) :current(u.base()) {};

			Iterator base() const {
				return current;
			};

			reference operator*() const {
				Iterator tmp = current;
				return *--tmp;
			};

			pointer operator->() const {
				return &(operator*());
			};

			reverse_iterator& operator++() {
				--current;
				return *this;
			};

			template <class U>
			reverse_iterator& operator=(const reverse_iterator<U> &u) {
				current = u.base();
				return *this;
			};

			reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				--current;
				return tmp;
			};

			reverse_iterator& operator--() {
				++current;
				return *this;
			};

			reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				++current;
				return tmp;
			};

			reverse_iterator operator+ (difference_type n) const {
				return reverse_iterator(current - n);
			};

			reverse_iterator& operator+=(difference_type n) {
				current -= n;
				return *this;
			};

			reverse_iterator operator- (difference_type n) const {
				return reverse_iterator(current + n);
			};

			reverse_iterator& operator-=(difference_type n) {
				current += n;
				return *this;
			};

			reference operator[](difference_type n) const {
				return current[-n - 1];
			};

			protected:

				Iterator current;
	};

	template <class Iterator1, class Iterator2>
	bool operator==( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y) {
		return x.base() == y.base();
	};

	template <class Iterator>
	bool operator==( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y) {
		return x.base() == y.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator<( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y) {
		return x.base() > y.base();
	};

	template <class Iterator>
	bool operator<( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y) {
		return x.base() > y.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y) {
		return x.base() != y.base();
	};

	template <class Iterator>
	bool operator!=(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y) {
		return x.base() != y.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y) {
		return x.base() < y.base();
	};

	template <class Iterator>
	bool operator>(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y) {
		return x.base() < y.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y) {
		return x.base() <= y.base();
	};

	template <class Iterator>
	bool operator>=(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y) {
		return x.base() <= y.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y) {
		return x.base() >= y.base();
	};

	template <class Iterator>
	bool operator<=(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y) {
		return x.base() >= y.base();
	};

	template <class Iterator1, class Iterator2>
	typename ft::reverse_iterator<Iterator1>::difference_type operator-(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y) {
		return y.base() - x.base();
	};

	template <class Iterator>
	typename ft::reverse_iterator<Iterator>::difference_type operator-(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y) {
		return y.base() - x.base();
	};

	template <class Iterator>
	ft::reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& x) {
		return ft::reverse_iterator<Iterator> (x.base() - n);
	};

}

#endif