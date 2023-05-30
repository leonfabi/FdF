/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:35:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/30 14:41:02 by fkrug            ###   ########.fr       */
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

void	ft_fill_map_content(char **tmp, t_mc *fdf)
{
	static int	call;
	int			count;

	while (tmp[count])
		count++;
	if (call == 0)
		fdf->x_len = count;
	else if (count != fdf->x_len)
		return (EXIT_FAILURE);
	count = 0;
	while (tmp[count])
	{
		
	}
}
t_mc	*ft_read_map(const char *pathname)
{
	int	fd;
	char	*map;
	char	**tmp;
	int		error;
	t_mc	*fdf;

	fd = open(pathname, O_RDONLY);
	map = get_next_line(fd);
	tmp = NULL;
	fdf = (t_mc *)malloc(sizeof(t_mc *));
	while (map && !error)
	{
		ft_printf("Map: %s\n", map);
		if (ft_check_map(map))
			error = 1;
		else
			tmp = ft_split(map, ' ');
		ft_free_2d(tmp);
		free(map);
		map = get_next_line(fd);
	}
	free(map);
}
