/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:48:06 by vsergio           #+#    #+#             */
/*   Updated: 2022/05/19 16:09:56 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*start_node;
	t_list	*temp;

	if (!del || !lst)
		return ;
	start_node = *lst;
	while (start_node)
	{
		temp = start_node->next;
		ft_lstdelone(start_node, del);
		start_node = temp;
	}
	*lst = NULL;
}
