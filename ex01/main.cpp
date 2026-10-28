/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 23:58:24 by aaycan            #+#    #+#             */
/*   Updated: 2026/10/29 01:45:09 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int	main(void)
{
	Data		data;
	Data		*ptr;
	uintptr_t	raw;

	data.id = 42;
	data.name = "Kocaeli";
	std::cout << "data.id              : " << data.id << std::endl;
	std::cout << "data.name            : " << data.name << std::endl;
	raw = Serializer::serialize(&data);
	ptr = Serializer::deserialize(raw);
	std::cout << "original address     : " << &data << std::endl;
	std::cout << "serialized (decimal) : " << raw << std::endl;
	std::cout << "serialized (hex)     : 0x" << std::hex << raw << std::dec << std::endl;
	std::cout << "deserialized address : " << ptr << std::endl;
	if (ptr == &data)
		std::cout << "result               : pointers are equal" << std::endl;
	else
		std::cout << "result               : pointers are NOT equal" << std::endl;
	std::cout << "ptr->id              : " << ptr->id << std::endl;
	std::cout << "ptr->name            : " << ptr->name << std::endl;
	return (0);
}
