/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:52:56 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/27 16:34:03 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	ft_close_window(mlx_t *mlx, mlx_image_t *img)
{
	mlx_delete_image(mlx, img);
	mlx_close_window(mlx);
	//mlx_terminate(mlx);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mc	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		ft_printf("ESC pressed\n");
		ft_close_window(fdf->mlx, fdf->img);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		fdf->x_trans = WIDTH / 2;
		fdf->y_trans = HEIGHT / 2;
		fdf->zoom = 1;
		ft_to_isometric(fdf);
	}
}

static void	ft_hook(void *param)
{
	ft_move_hook(param);
	ft_rotate_hook(param);
	ft_zoom_hook(param);
}
//#######################################################################################################
#include <time.h>

int	ft_init(t_mc *fdf)
{
	fdf->input = NULL;
	fdf->x_len = 0;
	fdf->y_len = 0;
	fdf->img = NULL;
	fdf->x_trans = WIDTH / 3;
	fdf->y_trans = HEIGHT / 3;
	fdf->zoom = 1;
	return (1);
}

int	ft_init_data(t_mc *fdf)
{
	int	y_size;
	
	y_size = 0;
	fdf->data = (t_point **)malloc(sizeof(t_point *) * fdf->y_len);
	if (fdf->data == NULL)
	{
		free(fdf->data);
		fdf->data = NULL;
		return (-1);
	}
	while (y_size < fdf->y_len)
	{
		fdf->data[y_size] = malloc(sizeof(t_point) * fdf->x_len);
		if (fdf->data[y_size] == NULL)
		{
			ft_free_data(fdf->data, y_size);
			return (-1);
		}
		y_size++;
	}
	return (1);
}

int	ft_fill_data(t_mc *fdf)
{
	int		x;
	int		y;
	char	**tmp;
	t_list	*lst;
	char	*string;
	clock_t start_time;
	double elapsed_time;
	clock_t end_time;

	x = 0;
	y = 0;
	lst = fdf->input;
	string = (char *)fdf->input->c;
	while (lst)
	{
		tmp = ft_split((char *)lst->c, ' ');
		x = 0;
		start_time = clock();
		while (tmp[x] != NULL)
		{
			fdf->data[y][x].z = ft_atoi(tmp[x]);
			fdf->data[y][x].y = y;
			fdf->data[y][x].x = x;
			fdf->data[y][x].y_draw = y;
			fdf->data[y][x].x_draw = x;
			x++;
		}
		//##########################################################################
		end_time = clock();
		elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

		// Print the elapsed time
		printf("SET_POINT: %.6f seconds\n", elapsed_time);
		//##########################################################################
		ft_free_2d(tmp);
		y++;
		lst = lst->next;
	}
	return (1);
}
//###############################################################################################################################3
int	main(int argc, char **argv)
{
	t_mc	fdf_new;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_init(&fdf_new);
	if (ft_read_map(&fdf_new, argv[1]) == -1)
		return (EXIT_FAILURE);
	ft_init_data(&fdf_new);
	mlx_set_setting(MLX_DECORATED, true);
	fdf_new.mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	if (!fdf_new.mlx)
		ft_error();
	fdf_new.img = mlx_new_image(fdf_new.mlx, WIDTH, HEIGHT);
	if (!fdf_new.img || (mlx_image_to_window(fdf_new.mlx, fdf_new.img, 0, 0) < 0))
	{
		ft_error();
		return (EXIT_FAILURE);
	}
	ft_fill_data(&fdf_new);
	ft_to_isometric(&fdf_new);
	mlx_key_hook(fdf_new.mlx, &my_keyhook, &fdf_new);
	mlx_loop_hook(fdf_new.mlx, ft_hook, &fdf_new);
	mlx_loop(fdf_new.mlx);
	mlx_close_window(fdf_new.mlx);
	mlx_terminate(fdf_new.mlx);
	ft_lstclear(&fdf_new.input, &free);
	ft_free_data(fdf_new.data, fdf_new.y_len - 1);
	//system("leaks FdF");
	return (1);
}
