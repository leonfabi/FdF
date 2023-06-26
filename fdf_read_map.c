/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:35:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/22 16:14:05 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_error_handler(char *str, int error, void *tmp, char **tmp2d)
{
	if (str != NULL)
		ft_printf("Error %s: %s\n", str, strerror(error));
	if (tmp != NULL)
		free(tmp);
	if (tmp2d != NULL)
		ft_free_2d(tmp2d);
	return (-1);
}

t_point	*ft_point_alloc(int x_pos, int y_pos, int z_pos)
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
	start->x_draw = SCALING * start->x;
	start->y_draw = SCALING * start->y;
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
			ft_lstadd_back(&(fdf->coord), \
			ft_lstnew(ft_point_alloc(count, y_pos, ft_atoi(tmp[count]))));
			count++;
		}
		if (call == 0)
			fdf->x_len = count;
		else if (count != fdf->x_len)
			return (ft_error_handler("Input map has wrong format", \
			5, map, tmp));
	}
	ft_free_2d(tmp);
	call++;
	return (0);
}
#include <time.h>
int	ft_read_map(t_mc *fdf, const char *pathname)
{
	int		fd;
	char	*map;
	int		y_pos;
	clock_t start_time;
	double elapsed_time;
	clock_t end_time;
	

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	map = get_next_line(fd);
	y_pos = 0;
	while (map)
	{
		start_time = clock();
		if (ft_fill_map_content(map, fdf, y_pos) == -1)
			return (-1);
		//##########################################################################
		end_time = clock();
		elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

		// Print the elapsed time
		printf("Read and fill one line: %.6f seconds\n", elapsed_time);
		//##########################################################################
		free(map);
		map = get_next_line(fd);
		y_pos++;
	}
	free(map);
	return (1);
}
