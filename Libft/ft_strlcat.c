/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:56:51 by fkrug             #+#    #+#             */
/*   Updated: 2023/03/28 16:37:05 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_l;
	size_t	c_d;
	size_t	c_s;

	dst_l = ft_strlen(dst);
	c_d = dst_l;
	c_s = 0;
	if (size > 0 && size > dst_l + 1)
	{
		while (src[c_s] && dst_l + c_s + 1 < size)
		{
			dst[c_d] = src[c_s];
			c_d++;
			c_s++;
		}
		dst[c_d] = '\0';
	}
	if (size <= dst_l)
		dst_l = size;
	return (ft_strlen(src) + dst_l);
}
