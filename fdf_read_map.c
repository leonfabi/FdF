/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:35:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/30 13:17:21 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_2d(char **tmp)
{
	int	count;

	count = 0;
	if (tmp != NULL)
	{
		while (tmp[count])
			free(tmp[count++]);
		free(tmp);
	}
}


int	ft_check_map(char *map)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (map[i])
	{
		if ((map[i] == '+' || map[i] == '-'))
		{
			if (!ft_isdigit(map[i + 1]))
				error = 1;
		}
		else if (!ft_isdigit(map[i]) && map[i] != ' ' && map[i] != '\n')
			error = 1;
		i++;
	}
	return (error);
}
void	ft_read_map(const char *pathname)
{
	int	fd;
	char	*map;
	char	**tmp;

	fd = open(pathname, O_RDONLY);
	map = get_next_line(fd);
	while (map)
	{
		ft_printf("Map: %sError: %d\n", map, ft_check_map(map));
		tmp = ft_split(map, ' ');
		ft_free_2d(tmp);
		free(map);
		map = get_next_line(fd);
	}
	free(map);
}