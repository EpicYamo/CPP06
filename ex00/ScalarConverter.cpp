/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 04:59:23 by aaycan            #+#    #+#             */
/*   Updated: 2026/10/27 05:28:03 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <limits>
#include <sstream>
#include <iomanip>

enum e_type
{
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_PSEUDO_FLOAT,
	TYPE_PSEUDO_DOUBLE,
	TYPE_INVALID
};

static e_type	detect_type(const std::string &str);
static bool		is_pseudo_float(const std::string &str);
static bool		is_pseudo_double(const std::string &str);
static bool		is_char(const std::string &str);
static bool		is_int(const std::string &str);
static bool		is_float(const std::string &str);
static bool		is_double(const std::string &str);
static void		from_char(const std::string &str);
static void		from_int(const std::string &str);
static void		from_float(const std::string &str);
static void		from_double(const std::string &str);
static void		print_values(double value);
static void		print_char(double value);
static void		print_int(double value);
static void		print_float(double value);
static void		print_double(double value);
static void		print_number(double value, int precision);
static void		print_impossible(void);

void	ScalarConverter::convert(const std::string &str)
{
	e_type	type;

	type = detect_type(str);
	switch (type)
	{
		case TYPE_CHAR:
			from_char(str);
			break ;
		case TYPE_INT:
			from_int(str);
			break ;
		case TYPE_FLOAT:
		case TYPE_PSEUDO_FLOAT:
			from_float(str);
			break ;
		case TYPE_DOUBLE:
		case TYPE_PSEUDO_DOUBLE:
			from_double(str);
			break ;
		case TYPE_INVALID:
			print_impossible();
			break ;
	}
}

static e_type	detect_type(const std::string &str)
{
	if (str.empty())
		return (TYPE_INVALID);
	if (is_pseudo_float(str))
		return (TYPE_PSEUDO_FLOAT);
	if (is_pseudo_double(str))
		return (TYPE_PSEUDO_DOUBLE);
	if (is_char(str))
		return (TYPE_CHAR);
	if (is_int(str))
		return (TYPE_INT);
	if (is_float(str))
		return (TYPE_FLOAT);
	if (is_double(str))
		return (TYPE_DOUBLE);
	return (TYPE_INVALID);
}

static bool	is_pseudo_float(const std::string &str)
{
	return ((str == "nanf") || (str == "+inff") || (str == "-inff")
		|| (str == "inff"));
}

static bool	is_pseudo_double(const std::string &str)
{
	return ((str == "nan") || (str == "+inf") || (str == "-inf")
		|| (str == "inf"));
}

static bool	is_char(const std::string &str)
{
	if ((str.length() == 1) && !std::isdigit(str[0]))
		return (true);
	if ((str.length() == 3) && (str[0] == '\'') && (str[2] == '\''))
		return (true);
	return (false);
}

static bool	is_int(const std::string &str)
{
	size_t	i;

	i = 0;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	if (i == str.length())
		return (false);
	while (i < str.length())
	{
		if (!std::isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_float(const std::string &str)
{
	if ((str.length() < 2) || (str[str.length() - 1] != 'f'))
		return (false);
	return (is_double(str.substr(0, str.length() - 1)));
}

static bool	is_double(const std::string &str)
{
	size_t	i;
	int		dot_count;
	int		digit_count;

	i = 0;
	dot_count = 0;
	digit_count = 0;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while (i < str.length())
	{
		if (str[i] == '.')
			dot_count++;
		else if (std::isdigit(str[i]))
			digit_count++;
		else
			return (false);
		i++;
	}
	return ((dot_count == 1) && (digit_count > 0));
}

static void	from_char(const std::string &str)
{
	char	c;

	if (str.length() == 3)
		c = str[1];
	else
		c = str[0];
	print_values(static_cast<double>(c));
}

static void	from_int(const std::string &str)
{
	long	value;
	int		i;

	errno = 0;
	value = std::strtol(str.c_str(), NULL, 10);
	if ((errno == ERANGE) || (value < std::numeric_limits<int>::min())
		|| (value > std::numeric_limits<int>::max()))
	{
		print_impossible();
		return ;
	}
	i = static_cast<int>(value);
	print_values(static_cast<double>(i));
}

static void	from_float(const std::string &str)
{
	double	value;
	float	f;

	errno = 0;
	value = std::strtod(str.c_str(), NULL);
	if (((errno == ERANGE) && ((value == HUGE_VAL) || (value == -HUGE_VAL)))
		|| ((std::fabs(value) > std::numeric_limits<float>::max())
		&& (value != std::numeric_limits<double>::infinity())
		&& (value != -std::numeric_limits<double>::infinity())))
	{
		print_impossible();
		return ;
	}
	f = static_cast<float>(value);
	print_values(static_cast<double>(f));
}

static void	from_double(const std::string &str)
{
	double	d;

	errno = 0;
	d = std::strtod(str.c_str(), NULL);
	if ((errno == ERANGE) && ((d == HUGE_VAL) || (d == -HUGE_VAL)))
	{
		print_impossible();
		return ;
	}
	print_values(d);
}

static void	print_values(double value)
{
	print_char(value);
	print_int(value);
	print_float(value);
	print_double(value);
}

static void	print_char(double value)
{
	char	c;

	std::cout << "char: ";
	if (!((value >= std::numeric_limits<char>::min())
			&& (value <= std::numeric_limits<char>::max())))
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	c = static_cast<char>(value);
	if (!std::isprint(static_cast<unsigned char>(c)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << c << "'" << std::endl;
}

static void	print_int(double value)
{
	std::cout << "int: ";
	if (!((value >= std::numeric_limits<int>::min())
			&& (value <= std::numeric_limits<int>::max())))
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	std::cout << static_cast<int>(value) << std::endl;
}

static void	print_float(double value)
{
	float	f;

	std::cout << "float: ";
	if ((std::fabs(value) > std::numeric_limits<float>::max())
		&& (value != std::numeric_limits<double>::infinity())
		&& (value != -std::numeric_limits<double>::infinity()))
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	f = static_cast<float>(value);
	print_number(static_cast<double>(f), std::numeric_limits<float>::digits10);
	std::cout << "f" << std::endl;
}

static void	print_double(double value)
{
	std::cout << "double: ";
	print_number(value, std::numeric_limits<double>::digits10);
	std::cout << std::endl;
}

static void	print_number(double value, int precision)
{
	std::ostringstream	oss;
	std::string			result;

	if (value != value)
	{
		std::cout << "nan";
		return ;
	}
	if (value == std::numeric_limits<double>::infinity())
	{
		std::cout << "+inf";
		return ;
	}
	if (value == -std::numeric_limits<double>::infinity())
	{
		std::cout << "-inf";
		return ;
	}
	oss << std::setprecision(precision) << value;
	result = oss.str();
	if ((result.find('.') == std::string::npos)
		&& (result.find('e') == std::string::npos))
		result += ".0";
	std::cout << result;
}

static void	print_impossible(void)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}
