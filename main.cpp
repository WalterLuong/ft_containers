/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:29:53 by wluong            #+#    #+#             */
/*   Updated: 2022/03/01 03:38:13 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include "vector.hpp"

int		main() {
	ft::vector<int>		vec(5, 10);

	std::cout << "size = " << vec.size() << std::endl;
	std::cout << "capacity = " << vec.capacity() << std::endl;

	std::cout << "vec [ ";
	for (int i(0); i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << "]" << std::endl;
	vec[2] = 3;
	std::cout << "test at : " << vec.at(2) << std::endl;
	vec.push_back(8);

	std::cout << "size = " << vec.size() << std::endl;
	std::cout << "capacity = " << vec.capacity() << std::endl;
	
	ft::vector<int>::iterator it = vec.begin();
	ft::vector<int>::iterator ite = vec.end();
	for (; it != ite; it++) {
		std::cout << *it << std::endl;
	}
}

#include <memory>
#include <string>

// int main(){
  
//   std::cout << std::endl;

//   std::allocator<int> intAlloc; 

//   std::cout << "intAlloc.max_size(): " << intAlloc.max_size() << std::endl;
//   int* intArray = intAlloc.allocate(100);

//   std::cout << "intArray[4]: " << intArray[4] << std::endl;
 
//   intArray[4] = 2011;

//   std::cout << "intArray[4]: " << intArray[4] << std::endl;
 
//   intAlloc.deallocate(intArray, 100);

//   std::cout << std::endl;
 
//   std::allocator<double> doubleAlloc;
//   std::cout << "doubleAlloc.max_size(): " << doubleAlloc.max_size() << std::endl;
  
//   std::cout << std::endl;

//   std::allocator<std::string> stringAlloc;
//   std::cout << "stringAlloc.max_size(): " << stringAlloc.max_size() << std::endl;
 
//   std::string* myString = stringAlloc.allocate(3); 
 
//   stringAlloc.construct(myString, "Hello");
//   stringAlloc.construct(myString + 1, "World");
//   stringAlloc.construct(myString + 2, "!");
 
//   std::cout << myString[0] << " " << myString[1] << " " << myString[2] << std::endl;
 
//   stringAlloc.destroy(myString);
//   stringAlloc.destroy(myString + 1);
//   stringAlloc.destroy(myString + 2);
//   stringAlloc.deallocate(myString, 3);
  
//   std::cout << std::endl;
  
// }