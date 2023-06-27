/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:35:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/27 16:34:43 by fkrug            ###   ########.fr       */
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
	return(1);
}
