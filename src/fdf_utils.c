/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:57:26 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/29 13:40:33 by fkrug            ###   ########.fr       */
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

void	ft_free_data(t_point **tmp, int y_size)
{
	if (tmp != NULL)
	{
		while (y_size >= 0)
		{
			free(tmp[y_size]);
			tmp[y_size] = 0;
			y_size--;
		}
		free(tmp);
	}
}

void	ft_error(void)
{
	printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	ft_reset(t_mc *fdf, int mode)
{
	if (mode == 2)
	{
		if (fdf->color)
			fdf->color = 0;
		else
			fdf->color = 1;
		ft_draw_grid(fdf, fdf->img);
		return ;
	}
	fdf->x_trans = WIDTH / 3;
	fdf->y_trans = HEIGHT / 3;
	fdf->zoom = 1;
	if (mode == 0)
		ft_to_isometric(fdf);
	else if (mode == 1)
		ft_to_xy(fdf);
	else if (mode == 3)
		ft_to_yz(fdf);
}

int	ft_close_window(t_mc *fdf, int input, int data, int mlx)
{
	if (input)
		ft_lstclear(&fdf->input, &free);
	if (data)
		ft_free_data(fdf->data, fdf->y_len - 1);
	if (mlx)
	{
		mlx_delete_image(fdf->mlx, fdf->img);
		mlx_close_window(fdf->mlx);
	}
		//mlx_terminate(fdf->mlx);
	return (-1);
}
