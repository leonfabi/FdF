/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:52:01 by fkrug             #+#    #+#             */
/*   Updated: 2023/05/11 18:08:01 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*counter;

	counter = *lst;
	if (!lst || !*lst || !del)
		return ;
	while (lst && *lst)
	{
		counter = (*lst)->next;
		ft_lstdelone(*lst, *del);
		*lst = counter;
	}
	*lst = NULL;
}
