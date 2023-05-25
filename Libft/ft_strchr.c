/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:07:52 by fkrug             #+#    #+#             */
/*   Updated: 2023/03/28 16:36:40 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	const char	*pointer;

	pointer = s;
	while (*pointer)
	{
		if (*pointer == (char)c)
			return ((char *)pointer);
		pointer++;
	}
	if (*pointer == (char)c)
		return ((char *)pointer);
	return (NULL);
}
