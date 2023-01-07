/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:40 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/07 19:09:15 by vsergio          ###   ########.fr       */
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

void	change_content(char *name, char *content, t_var_lst *variables)
{
	t_var_lst	*temp;
	int			name_len;

	temp = variables;
	name_len = ft_strlen(name);
	while (temp && ft_strncmp(name, temp->name, name_len + 1))
		temp = temp->next;
	if (temp)
	{
		free(temp->content);
		temp->content = content;
	}
}

t_var_lst	*get_env(char *name, t_var_lst *variables)
{
	t_var_lst	*temp;
	int			name_len;

	temp = variables;
	name_len = ft_strlen(name);
	while (temp && ft_strncmp(name, temp->name, name_len + 1))
		temp = temp->next;
	return (temp);
}
