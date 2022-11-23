/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:28:59 by vsergio           #+#    #+#             */
/*   Updated: 2022/05/19 11:30:16 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lastnode;

	if (lst == NULL)
		return (NULL);
	lastnode = lst;
	while (lst->next != NULL)
	{
		lastnode = lst->next;
		lst = lst->next;
	}
	return (lastnode);
}
