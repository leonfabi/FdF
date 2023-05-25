/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:43:10 by fkrug             #+#    #+#             */
/*   Updated: 2023/03/28 16:35:34 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*pointer;

	pointer = s;
	if (n > 0)
	{
		while (n > 1 && *pointer != (unsigned char)c)
		{
			pointer++;
			n--;
		}
		if (*pointer == (unsigned char)c)
			return ((char *) pointer);
	}
	return (NULL);
}
