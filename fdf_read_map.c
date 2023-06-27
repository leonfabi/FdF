/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:35:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/27 17:51:23 by fkrug            ###   ########.fr       */
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

int	ft_get_x_len(char *line)
{
	char	**tmp;
	int		count;

	count = 0;
	tmp = ft_split(line, ' ');
	while (tmp[count])
		count++;
	ft_free_2d(tmp);
	return (count);
}

int	ft_read_map(t_mc *fdf, const char *pathname)
{
	int		fd;
	char	*map;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	map = get_next_line(fd);
	fdf->x_len = ft_get_x_len(map);
	while (map != NULL)
	{
		ft_lstadd_back(&(fdf->input), ft_lstnew(map));
		map = get_next_line(fd);
		fdf->y_len++;
	}
	close(fd);
	free(map);
	return (1);
}

int	ft_fill_data(t_mc *fdf)
{
	int		x;
	int		y;
	char	**tmp;
	t_list	*lst;

	x = 0;
	y = 0;
	lst = fdf->input;
	while (lst && y < fdf->y_len)
	{
		tmp = ft_split((char *)lst->c, ' ');
		x = 0;
		while (tmp[x] != NULL && x < fdf->x_len)
		{
			fdf->data[y][x].z = ft_atoi(tmp[x]);
			fdf->data[y][x].y = y;
			fdf->data[y][x].x = x;
			x++;
		}
		ft_free_2d(tmp);
		y++;
		lst = lst->next;
	}
	return (1);
}
