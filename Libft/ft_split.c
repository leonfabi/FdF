/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:20:49 by fkrug             #+#    #+#             */
/*   Updated: 2023/03/28 18:34:25 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sections(char const *s, char c)
{
	int	start;
	int	end;
	int	len;

	start = 0;
	end = 0;
	len = 0;
	while (s[start])
	{
		if (s[start] == c)
			start++;
		else
		{
			end = start;
			while (s[end] != c && s[end])
				end++;
			len += 1;
			if (!s[end])
				start = end;
			else
				start = end + 1;
		}
	}
	return (len);
}

static int	ft_sect_start(char const *s, char c, int old_end)
{
	int	start;

	start = old_end + 1;
	while (s[start] == c)
		start++;
	return (start);
}

static int	ft_sect_end(char const *s, char c, int old_start)
{
	int	end;

	end = old_start;
	while (s[end] != c && s[end])
		end++;
	end--;
	return (end);
}

static void	ft_free(char **arr, int c)
{
	while (c > 1)
	{
		free(arr[c - 2]);
		c--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**array;
	int		start;
	int		end;
	int		count;

	start = 0;
	end = -1;
	count = 0;
	len = ft_sections(s, c);
	array = (char **)ft_calloc(len + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (count < len)
	{
		start = ft_sect_start(s, c, end);
		end = ft_sect_end(s, c, start);
		array[count] = ft_substr(s, start, end - start + 1);
		if (!array[count++])
		{
			ft_free(array, count);
			return (NULL);
		}
	}
	return (array);
}
