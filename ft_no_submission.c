/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_submission.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:40:53 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/21 14:02:32 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_put_map(t_mc *fdf)
{
	t_list	*tmp;

	tmp = fdf->coord;
	ft_printf("Print Coordinates a:\n______\n");
	while (tmp)
	{
		ft_printf("(X:\t%d\t|Y:\t%d\t|Z:\t%d\t)\n", ((t_point *)tmp->c)->x, ((t_point *)tmp->c)->y, ((t_point *)tmp->c)->z);
		tmp = tmp->next;
	}
	ft_printf("END\n");
}

void	ft_draw_map(mlx_image_t *img, t_mc *fdf)
{
	t_list	*tmp;

	tmp = fdf->coord;
	while (tmp)
	{
		if (((t_point *) tmp->c)->x_draw >= 0 && ((t_point *) tmp->c)->y_draw >=0)
			mlx_put_pixel(img, (1) * ((t_point *) tmp->c)->x_draw,(1) * ((t_point *) tmp->c)->y_draw, 0xFF0000FF);
		tmp = tmp->next;
	}
}