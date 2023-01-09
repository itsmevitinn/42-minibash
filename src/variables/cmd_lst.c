/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:02:11 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/08 21:13:28 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_lst	*ft_cmd_new(char *line)
{
	t_cmd_lst	*lst;

	lst = malloc(sizeof(t_cmd_lst));
	if (!lst)
		return (NULL);
	lst->in_file = NULL;
	lst->out_file = NULL;
	lst->input = 0;
	lst->output = 1;
	lst->line = line;
	lst->args = NULL;
	lst->next = NULL;
	lst->delimiter = NULL;
	lst->not_found = 0;
	return (lst);
}

void	ft_cmdadd_back(t_cmd_lst **head, t_cmd_lst *new)
{
	t_cmd_lst	*temp;

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

void	ft_cmdclear(t_cmd_lst **head)
{
	t_cmd_lst	*ptr;

	ptr = *head;
	while (ptr)
	{
		free(ptr->in_file);
		free(ptr->out_file);
		if (ptr->input > 2)
			close(ptr->input);
		if (ptr->output > 2)
			close(ptr->output);
		free(ptr->delimiter);
		free(ptr->line);
		if (ptr->args)
			free_matrix(ptr->args);
		ptr = ptr->next;
		free(*head);
		*head = ptr;
	}
}
