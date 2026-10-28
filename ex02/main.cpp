/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 01:16:24 by aaycan            #+#    #+#             */
/*   Updated: 2026/10/29 01:47:15 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.hpp"
#include <iostream>
#include <cstddef>

int	main(void)
{
	Base	*p;
	int		i;

	i = 0;
	while (i < 5)
	{
		p = generate();
		std::cout << "identify(Base *): ";
		identify(p);
		std::cout << "identify(Base &): ";
		identify(*p);
		std::cout << std::endl;
		delete p;
		i++;
	}
	p = new Base;
	std::cout << "plain Base (Base *): ";
	identify(p);
	std::cout << "plain Base (Base &): ";
	identify(*p);
	delete p;
	std::cout << "NULL pointer       : ";
	identify(static_cast<Base *>(NULL));
	return (0);
}
