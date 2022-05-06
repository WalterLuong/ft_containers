/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:30:10 by wluong            #+#    #+#             */
/*   Updated: 2022/05/06 18:36:54 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <iostream>
# include <iostream>
# include <algorithm>
# include <memory>
# include <cstddef>
# include "rbt_iterator.hpp"
# include "red_black_tree.hpp"
# include "lexicographical_compare.hpp"

namespace ft {
	template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set {

		public:

			typedef Key										key_type;
			typedef Key										value_type;
			typedef Compare									key_compare;
			typedef Compare									value_compare;
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef ft::RBTIterator<value_type>				iterator;
			typedef ft::const_RBTIterator<value_type>		const_iterator;
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::difference_type		difference_type;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		public:

/***************************************************************************
****************************************************************************
*************					CONSTRUCTEURS					************
****************************************************************************
***************************************************************************/

			explicit set(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : rbt(value_compare(comp)), _alloc(alloc), _cmp(comp) {};

			template <class InputIterator>
			set(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : rbt(value_compare(comp)), _alloc(alloc), _cmp(comp) {
				insert(first, last);
			};

			set(const set<Key,Compare,Allocator>& x) : rbt(value_compare(x._cmp)), _alloc(Allocator()), _cmp(Compare()) {
				insert(x.begin(), x.end());
			};

			~set() {};

			set<Key,Compare,Allocator>& operator= (const set<Key,Compare,Allocator>& x) {
				this->clear();
				const_iterator it = x.begin();
				for (; it != x.end(); it++) {
				insert(*it);
				}
				return *this;
			};
			
			allocator_type get_allocator() const { return _alloc; };

/***************************************************************************
****************************************************************************
*************					ITERATORS						************
****************************************************************************
***************************************************************************/

			iterator begin() { return rbt.begin(); };

			const_iterator begin() const { return rbt.begin(); };

			iterator end() { return rbt.end(); };

			const_iterator end() const { return rbt.end(); };

			reverse_iterator rbegin() { return rbt.rbegin(); };

			const_reverse_iterator rbegin() const { return rbt.rbegin(); };

			reverse_iterator rend() { return rbt.rend(); };

			const_reverse_iterator rend() const { rbt.rend(); };

/***************************************************************************
****************************************************************************
*************					SIZE							************
****************************************************************************
***************************************************************************/

			bool empty() const { return rbt.empty(); };

			size_type size() const { return rbt.size(); };
			
			size_type max_size() const { return rbt.max_size(); };

/***************************************************************************
****************************************************************************
*************					MODIFIERS						************
****************************************************************************
***************************************************************************/

			pair<iterator,bool> insert(const value_type& x) {
				iterator f = find(x);
				iterator it = iterator(rbt.insert(x), rbt.getNil(), rbt.getRoot());
				if (f.get_node() != rbt.getNil())
					return ft::make_pair(it, 0);
				return ft::make_pair(it, 1);
			};

			iterator insert(iterator position, const value_type& x) {
				(void)position;
				return iterator(rbt.insert(x), rbt.getNil(), rbt.getRoot());
			};

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				for (; first != last; first++) {
					insert(*first);
				}
			};

			void erase(iterator position) {
				rbt.erase(*position);
			};

			size_type erase(const key_type& x) {
				return rbt.erase(x);
			};

			void erase(iterator first, iterator last) {
				iterator tmp;
				while (first != last) {
					tmp = first;
					tmp++;
					erase(first);
					first = tmp;
				}
			};

			void swap(set<Key,Compare,Allocator>& other) {
				rbt.swap(other.rbt);
				std::swap(_alloc, other._alloc);
				std::swap(_cmp, other._cmp);
			};

			void clear() {
				rbt.clear();
			};

/***************************************************************************
****************************************************************************
*************					OBSERVERS						************
****************************************************************************
***************************************************************************/

			key_compare key_comp() const {
				return key_compare();
			};

			value_compare value_comp() const {
				return value_compare(key_compare());
			};

/***************************************************************************
****************************************************************************
*************					SET OPERATIONS					************
****************************************************************************
***************************************************************************/

			iterator find(const key_type& x) {
				return rbt.find(x);
			};

			const_iterator find(const key_type& x) const {
				return rbt.find(x);
			};

			size_type count(const key_type& x) const {
				return rbt.count(x);
			};

			iterator lower_bound(const key_type& x) {
				return rbt.lower_bound(x);
			};

			const_iterator lower_bound(const key_type& x) const {
				return rbt.lower_bound(x);
			};

			iterator upper_bound(const key_type& x) {
				return rbt.upper_bound(x);
			};

			const_iterator upper_bound(const key_type& x) const {
				return rbt.upper_bound(x);
			};
			
			pair<iterator,iterator>
			equal_range(const key_type& x) {
				return ft::make_pair(lower_bound(x), upper_bound(x));
			};

			pair<const_iterator,const_iterator>
			equal_range(const key_type& x) const {
				return ft::make_pair(lower_bound(x), upper_bound(x));
			};

			private :

			RedBlackTree<value_type, value_compare>		rbt;
			allocator_type								_alloc;
			value_compare								_cmp;
	};
	
		template <class Key, class Compare, class Allocator>
		bool operator==(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
			if (x.size() != y.size())
				return false;
			return ft::equal(x.begin(), x.end(), y.begin());
		};

		template <class Key, class Compare, class Allocator>
		bool operator< (const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		};

		template <class Key, class Compare, class Allocator>
		bool operator!=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
			return (!(x == y));
		};

		template <class Key, class Compare, class Allocator>
		bool operator> (const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
			return (y < x);
		};

		template <class Key, class Compare, class Allocator>
		bool operator>=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
			return (!(x < y));
		};

		template <class Key, class Compare, class Allocator>
		bool operator<=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
			return (!(y < x));
		};

		template <class Key, class Compare, class Allocator>
		void swap(set<Key,Compare,Allocator>& x, set<Key,Compare,Allocator>& y) {
			x.swap(y);
		};
};

#endif