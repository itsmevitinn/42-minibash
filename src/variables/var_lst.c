/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:40 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/08 15:59:32 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_var_lst	*ft_var_new(char *name, void *content)
{
	t_var_lst	*lst;

	lst = malloc(sizeof(t_var_lst));
	if (!lst)
		return (NULL);
	lst->name = name;
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

void	ft_varadd_back(t_var_lst **head, t_var_lst *new)
{
	t_var_lst	*temp;

	if (!*head || !head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_varclear(t_var_lst **head)
{
	t_var_lst	*ptr;

	ptr = *head;
	while (ptr)
	{
		free(ptr->name);
		free(ptr->content);
		ptr = ptr->next;
		free(*head);
		*head = ptr;
	}
}
