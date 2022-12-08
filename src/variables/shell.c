/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:14:20 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/07 23:45:53 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static void	ft_var_addback(t_var_list **lst, t_var_list *new);
static t_var_list	*ft_var_new(char *name, void *content);
static t_var_list	*ft_var_last(t_var_list *lst);

void	initialize_var(t_var_list *lst)
{
	ft_var_addback(&lst, ft_var_new("?", &exit_status));
}

static t_var_list	*ft_var_new(char *name, void *content)
{
	t_var_list	*lst;

	lst = (t_var_list *)malloc(sizeof(t_var_list));
	if (!lst)
		return (NULL);
	lst->name = name;
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

static t_var_list	*ft_var_last(t_var_list *lst)
{
	t_var_list	*lastnode;

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

static void	ft_var_addback(t_var_list **lst, t_var_list *new)
{
	t_var_list	*temp;

	if (!*lst || !lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_var_last(*lst);
	temp->next = new;
}