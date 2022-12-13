/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:44:40 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/13 17:27:52 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_lst *ft_cmd_new(char *cmd_line)
{
	t_cmd_lst *lst;

	lst = malloc(sizeof(t_cmd_lst));
	if (!lst)
		return (NULL);
	lst->cmd_line = cmd_line;
	lst->next = NULL;
	return (lst);
}

t_var_lst *ft_var_new(char *name, void *content)
{
	t_var_lst *lst;

	lst = malloc(sizeof(t_var_lst));
	if (!lst)
		return (NULL);
	lst->name = name;
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

void ft_cmdadd_back(t_cmd_lst **head, t_cmd_lst *new)
{
	t_cmd_lst *temp;

	if (!*head || !head)
	{
		*head = new;
		return;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void ft_varadd_back(t_var_lst **head, t_var_lst *new)
{
	t_var_lst *temp;

	if (!*head || !head)
	{
		*head = new;
		return;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void ft_varclear(t_var_lst **head)
{
	t_var_lst *ptr;

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

void change_content(char *name, char *content, t_var_lst *variables)
{
	int name_len;

	name_len = ft_strlen(name);
	while (variables && ft_strncmp(name, variables->name, name_len + 1))
		variables = variables->next;
	if (variables)
	{
		free(variables->content);
		variables->content = content;
	}
}

int is_env(char *name, t_var_lst *variables)
{
	int name_len;

	name_len = ft_strlen(name);
	while (variables && ft_strncmp(name, variables->name, name_len + 1))
		variables = variables->next;
	if (variables)
		return (1);
	return (0);
}
