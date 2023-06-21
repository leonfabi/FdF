/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_submission.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:40:53 by fkrug             #+#    #+#             */
/*   Updated: 2023/06/21 12:40:55 by fkrug            ###   ########.fr       */
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