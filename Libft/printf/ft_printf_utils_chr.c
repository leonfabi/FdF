/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_chr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:45:44 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/10 15:42:57 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putchar_print(char c, int *print)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	(*print)++;
	return (0);
}

int	ft_putstr_print(char *s, int *print)
{
	if (s == NULL)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		(*print) += 6;
	}
	else
	{
		if (write(1, s, ft_strlen(s)) < 0)
			return (-1);
		(*print) += ft_strlen(s);
	}
	return (0);
}

int	ft_putptr_print(void *ptr, int *print)
{
	if (ptr != NULL)
	{
		if (ft_putstr_print("0x", print) < 0)
			return (-1);
		if (ft_xtoa_l_print((size_t) ptr, print) < 0)
			return (-1);
	}
	else
		if (ft_putstr_print("0x0", print) < 0)
			return (-1);
	return (0);
}
