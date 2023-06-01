/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:35:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/31 17:11:11 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_error_handler(char *str, int error)
{
	ft_printf("Error %s: %s\n", str, strerror(error));
	return (-1);
}

int	ft_check_map(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if ((map[i] == '+' || map[i] == '-'))
		{
			if (!ft_isdigit(map[i + 1]))
			{
				free(map);
				return (ft_error_handler("Input map sign", 42));
			}
		}
		else if (!ft_isdigit(map[i]) && map[i] != ' ' && map[i] != '\n')
		{
			free(map);
			return (ft_error_handler("Input map contains non-digits", 42));
		}
		i++;
	}
	if (map[i - 1] == '\n')
		map[i - 1] = '\0';
	return (0);
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
	int		y_pos;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (NULL);
	}
	map = get_next_line(fd);
	tmp = NULL;
	y_pos = 0;
	while (map)
	{
		ft_printf("Map: %s\n", map);
		if (ft_check_map(map) == -1)
			return (NULL);
		tmp = ft_split(map, ' ');
		ft_fill_map_content(tmp, fdf, y_pos);
		ft_free_2d(tmp);
		free(map);
		map = get_next_line(fd);
		y_pos++;
	}
	free(map);
}
