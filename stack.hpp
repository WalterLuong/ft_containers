/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 04:30:11 by wluong            #+#    #+#             */
/*   Updated: 2022/03/09 04:42:07 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {

	template < class T, class C = ft::vector<T> >
	class stack {

		protected:
			C	c;

		public:
		typedef typename C::value_type		value_type;
		typedef typename C::size_type		size_type;
		typedef C							container_type;

		explicit stack(const C& a = C()) : c(a){};

		bool empty() const { return c.empty(); };

		size_type size() const { return c.size(); };


		const value_type& top() const { return c.back(); };
		// value_type& top() const { return c.back(); };

		void push(const value_type& n) { c.push_back(n); };

		void pop() { c.pop_back(); };
		
	};

}

#endif