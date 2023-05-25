/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:04:16 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/23 14:23:46 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *c)
{
	t_list	*start;

	start = (t_list *)malloc(sizeof(t_list));
	if (start == NULL)
		return (NULL);
	start->c = c;
	start->next = NULL;
	return (start);
}
