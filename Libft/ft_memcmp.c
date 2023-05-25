/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:07:09 by fkrug             #+#    #+#             */
/*   Updated: 2023/03/28 16:35:40 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*src1;
	unsigned const char	*src2;

	src1 = s1;
	src2 = s2;
	if (n == 0)
		return (0);
	else
	{
		while (n > 1 && (*src1 - *src2) == 0)
		{
			n--;
			src1++;
			src2++;
		}
		return ((unsigned char)*src1 - (unsigned char)*src2);
	}
}
