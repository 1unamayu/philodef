/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:50:04 by xamayuel          #+#    #+#             */
/*   Updated: 2024/01/28 10:55:18 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_check_over_long(int sign, unsigned long long int number);

/**
 * NAME: ft_atoi()
 * 
 * DESCRIPTION:
 * 		Converts the initial portion of the string to integer
 * 
 * RETURN:
 *		The int value (if exists) of converted string.
 *
 * PARAMS:
 * 		@param str: pointer to the string
 * 
 * TIPS:
 * 		1. - check spaces
 * 		2. - check + and -. If else if
 * 		3. - while number, *10 + number
 * 
 */
int	ft_atoi(const char *str)
{
	int						sign;
	unsigned long long int	number;
	int						count;

	count = 0;
	sign = 1;
	number = 0;
	while (str[count] == ' ' || str[count] == '\n' || str[count] == '\f' || \
			str[count] == '\t' || str[count] == '\v' || str[count] == '\r')
		count++;
	if (str[count] == '+')
		count++;
	else if (str[count] == '-')
	{
		sign = -1;
		count ++;
	}
	while (str[count] >= '0' && str[count] <= '9')
	{
		number = number * 10;
		number += str[count] - 48;
		count ++;
	}
	return (ft_check_over_long(sign, number));
}

static int	ft_check_over_long(int sign, unsigned long long int number)
{
	if (number >= 9223372036854775808ULL)
	{
		if (sign == 1)
			number = 1;
		else
			number = 0;
		sign = -sign;
	}
	if (sign < 0)
		return (-number);
	else
		return (number);
}
