/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:59:54 by fkrug             #+#    #+#             */
/*   Updated: 2023/03/28 17:25:07 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, char const *set)
{
	int	subset;

	subset = 0;
	while (*set)
	{
		if (c == *set)
			subset = 1;
		set++;
	}
	return (subset);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trim;
	int		count;

	start = 0;
	end = 0;
	count = 0;
	while (isset(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (isset(s1[end], set) && end >= start)
		end--;
	trim = (char *)malloc(end - start + 2);
	if (trim == NULL)
		return (NULL);
	while (start <= end)
	{
		trim[count] = s1[start];
		count++;
		start++;
	}
	trim[count] = '\0';
	return (trim);
}
