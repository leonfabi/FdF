/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:11:01 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/10 15:38:40 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_type(va_list ap, const char *string, int *print)
{
	int	i;

	i = 0;
	if (string[1] == 'c')
		i = ft_putchar_print(va_arg(ap, int), print);
	else if (string[1] == 's')
		i = ft_putstr_print(va_arg(ap, char *), print);
	else if (string[1] == 'd' || string[1] == 'i')
		i = ft_putnbr_print(va_arg(ap, int), print);
	else if (string[1] == '%')
		i = ft_putchar_print('%', print);
	else if (string[1] == 'u')
		i = ft_putnbr_print(va_arg(ap, unsigned int), print);
	else if (string[1] == 'x')
		i = ft_xtoa_l_print(va_arg(ap, unsigned int), print);
	else if (string[1] == 'X')
		i = ft_xtoa_u_print(va_arg(ap, unsigned int), print);
	else if (string[1] == 'p')
		i = ft_putptr_print(va_arg(ap, char *), print);
	return (i);
}

int	ft_printf(const char *string, ...)
{
	va_list		ptr;
	int			count;
	int			print;

	count = -1;
	print = 0;
	va_start(ptr, string);
	if (!string)
		return (0);
	while (string[++count])
	{
		if (string[count] != (int)37)
		{
			if (ft_putchar_print(string[count], &print) < 0)
				return (-1);
		}
		else if (string[count] == (int)37)
		{
			if (ft_type(ptr, &string[count++], &print) < 0)
				return (-1);
		}
	}
	va_end(ptr);
	return (print);
}
