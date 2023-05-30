/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:35:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/30 16:30:05 by fkrug            ###   ########.fr       */
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
	if (map[i - 1] == '\n')
		map[i - 1] = '\0';
	return (error);
}
t_point *ft_point_alloc(int x_pos, int y_pos, int z_pos)
{
	t_point	*start;

	start = (t_point *)malloc(sizeof(t_point));
	if (start == NULL)
		return (NULL);
	start->x = x_pos;
	start->z = z_pos;
	start->y = y_pos;
	return (start);
}

int	ft_fill_map_content(char **tmp, t_mc *fdf, int y_pos)
{
	static int	call;
	int			count;
	t_point		*point;

	count = 0;
	point = NULL;
	if (tmp != NULL && fdf != NULL)
	{
		while (tmp[count])
			count++;
		if (call == 0)
			fdf->x_len = count;
		else if (count != fdf->x_len)
			return (EXIT_FAILURE);
		count = 0;
		while (tmp[count])
		{
			point = ft_point_alloc(count, y_pos, ft_atoi(tmp[count]));
			//ft_printf("Point: x: %d, y%d, z%d\n", point->x, point->y, point->z);
			ft_lstadd_back(&(fdf->coord), ft_lstnew(point));
			//ft_printf("(X:\t%d\t|Y:\t%d\t|Z:\t%d\t)\n", ((t_point *)fdf->coord->c)->x, ((t_point *)fdf->coord->c)->y, ((t_point *)fdf->coord->c)->z);
			count++;
		}
	}
	call++;
}


t_mc	*ft_read_map(t_mc *fdf, const char *pathname)
{
	int		fd;
	char	*map;
	char	**tmp;
	int		error;
	int		y_pos;

	fd = open(pathname, O_RDONLY);
	map = get_next_line(fd);
	tmp = NULL;
	y_pos = 0;
	error = 0;
	while (map && !error)
	{
		ft_printf("Map: %s\n", map);
		error = ft_check_map(map);
		if (!error)
		{
			tmp = ft_split(map, ' ');
			ft_fill_map_content(tmp, fdf, y_pos);
		}
		ft_free_2d(tmp);
		free(map);
		map = get_next_line(fd);
		y_pos++;
	}
	free(map);
}
