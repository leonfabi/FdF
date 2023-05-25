/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:37:35 by fkrug             #+#    #+#             */
/*   Updated: 2023/03/28 16:37:30 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const char	*src1;
	const char	*src2;

	src1 = s1;
	src2 = s2;
	if (n == 0)
		return (0);
	else
	{
		while (n > 1 && (*src1 - *src2) == 0 && *src1)
		{
			n--;
			src1++;
			src2++;
		}
		return ((unsigned char)*src1 - (unsigned char)*src2);
	}
}
