/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:42:03 by fkrug             #+#    #+#             */
/*   Updated: 2023/03/28 16:37:24 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	iterate;
	size_t			length;
	char			*str;

	length = ft_strlen(s);
	str = (char *) malloc(length + 1);
	if (str == NULL)
		return (NULL);
	iterate = 0;
	while (s[iterate])
	{
		str[iterate] = (*f)(iterate, s[iterate]);
		iterate++;
	}
	str[iterate] = '\0';
	return (str);
}
