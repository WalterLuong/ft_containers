/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 02:22:47 by wluong            #+#    #+#             */
/*   Updated: 2022/04/07 01:54:37 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {


	template <class T1, class T2>
	struct pair {
		
		typedef T1	first_type;
		typedef T2	second_type;
	
		first_type	first;
		second_type	second;
	
		pair() {};
	
		template<class U, class V>
		pair (const pair< U, V >& pr) {
			this->first = pr->first;
			this->second = pr->second;
		};
		
		pair (const first_type& a, const second_type& b) {
			this->first = a;
			this->second = b;
		};

		pair& operator= (const pair& pr) {
			this->first = pr->first;
			this->second = pr->second;
			return *this;
		};
	};
	
	template< class T1, class T2 >
	ft::pair<T1,T2>		make_pair( T1 t, T2 u ) {
		return ft::pair<T1, T2>(t, u);
	};

	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; };

	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs==rhs); };

	template <class T1, class T2>
	bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); };

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(rhs<lhs); };

	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return rhs<lhs; };

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs<rhs); };

}


#endif