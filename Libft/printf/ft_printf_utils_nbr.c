/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_nbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:48:53 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/10 15:38:46 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_print(long n, int *print)
{
	long	number;

	if (n < 0)
	{
		n *= -1;
		if (ft_putchar_print('-', print) < 0)
			return (-1);
	}
	number = n % 10;
	if (n > 9)
	{
		if (ft_putnbr_print(n / 10, print) < 0)
			return (-1);
		if (ft_putnbr_print(n % 10, print) < 0)
			return (-1);
		return (0);
	}
	else
	{
		if (ft_putchar_print(number + 48, print) < 0)
			return (-1);
		return (0);
	}
}

int	ft_xtoa_l_print(size_t integer, int *print)
{
	size_t	hex;

	hex = integer % 16;
	if (integer > 15)
	{
		if (ft_xtoa_l_print(integer / 16, print) < 0)
			return (-1);
	}
	if (hex > 9)
	{
		if (ft_putchar_print('a' + (hex - 10), print) < 0)
			return (-1);
		return (0);
	}
	else
	{
		if (ft_putchar_print(hex + '0', print) < 0)
			return (-1);
		return (0);
	}
}

int	ft_xtoa_u_print(size_t integer, int *print)
{
	size_t	hex;

	hex = integer % 16;
	if (integer > 15)
	{
		if (ft_xtoa_u_print(integer / 16, print) < 0)
			return (-1);
	}
	if (hex > 9)
	{
		if (ft_putchar_print('A' + (hex - 10), print))
			return (-1);
		return (0);
	}
	else
	{
		if (ft_putchar_print(hex + '0', print))
			return (-1);
		return (0);
	}
}
