/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:35:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/20 15:48:56 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_error_handler(char *str, int error, void *tmp)
{
	ft_printf("Error %s: %s\n", str, strerror(error));
	if (tmp != NULL)
		free(tmp);
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
				return (ft_error_handler("Input map sign", 5, map));
		}
		else if (!ft_isdigit(map[i]) && map[i] != ' ' && map[i] != '\n')
			return (ft_error_handler("Input map contains non-digits", 5, map));
		i++;
	}
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
	start->x_proj = x_pos;
	start->z_proj = z_pos;
	start->y_proj = y_pos;
	start->x_draw = SCALING * start->x;//round(cos(M_PI / 6) * SCALING * start->x + sin(M_PI / 6) * SCALING * start->y);//round(SCALING * (x_pos - z_pos) / sqrt(2));
	start->y_draw = SCALING * start->y;//round(cos(M_PI / 6) * SCALING * start->y - sin(M_PI / 6) * SCALING * start->x);//round(SCALING * (2 * y_pos + x_pos + z_pos) / sqrt(6));
	return (start);
}

int	ft_fill_map_content(char *map, t_mc *fdf, int y_pos)
{
	static int	call;
	int			count;
	char		**tmp;

	count = 0;
	tmp = ft_split(map, ' ');
	if (tmp != NULL && fdf != NULL)
	{
		fdf->y_len = (y_pos + 1);
		while (tmp[count] && tmp[count][0] != '\n')
		{
			ft_lstadd_back(&(fdf->coord), ft_lstnew(ft_point_alloc(count, y_pos, ft_atoi(tmp[count]))));
			count++;
		}
		if (call == 0)
			fdf->x_len = count;
		else if (count != fdf->x_len)
		{
			ft_free_2d(tmp);
			return (ft_error_handler("Input map has wrong format", 5, map));
		}
	}
	ft_free_2d(tmp);
	call++;
	return (0);
}


t_mc	*ft_read_map(t_mc *fdf, const char *pathname)
{
	int		fd;
	char	*map;
	int		y_pos;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (NULL);
	}
	map = get_next_line(fd);
	y_pos = 0;
	while (map)
	{
		ft_printf("Map: %s\n", map);
		if (ft_check_map(map) == -1)
			return (NULL);
		if (ft_fill_map_content(map, fdf, y_pos) == -1)
			return (NULL);
		free(map);
		map = get_next_line(fd);
		y_pos++;
	}
	free(map);
}
