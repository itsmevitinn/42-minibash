/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:10:07 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/15 17:00:06 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	name_is_invalid(char *cmd);
static void	remove_var(t_var_lst **var_lst, char *name);
static t_var_lst	*get_previous(char *name, t_var_lst *lst);

void	unset(char **cmd, t_var_lst **env_lst, int fd)
{
	int	exit_status;

	exit_status = 0;
	cmd++;
	while (*cmd)
	{
		if (name_is_invalid(*cmd))
		{
			print_error(*cmd, fd);
			exit_status = 1;
		}
		else if (get_env(name, var_lst))
			remove_var(var_lst, name);
		cmd++;
	}
	g_exit_status = exit_status;
}

static int	name_is_invalid(char *cmd)
{
	while (*cmd)
	{
		if (!ft_isalpha(*cmd) && *cmd != '_')
			return (1);
		cmd++;
	}
	return (0);
}

static void	print_error(char *cmd, fd)
{
	ft_putstr_fd("bash: unset `", fd);
	ft_putstr_fd(cmd ,fd);
	ft_putstr_fd("\': not a valid identifier\n", fd);
}

static void	remove_var(t_var_lst **var_lst, char *name)
{
	t_var_lst	*previous;
	t_var_lst	*temp;

	previous  = get_previous(name, *var_lst);
	if (!previous)
	{
		temp = *var_lst;
		*var_lst = (*var_lst)->next;
	}
	else
	{
		temp = get_env(name, *var_lst);
		previous->next = temp->next;
	}
	free(temp->name);
	free(temp->content);
	free(temp);
}

static t_var_lst	*get_previous(char *name, t_var_lst *lst)
{
	int	name_len;

	name_len = ft_strlen(name);
	if (!ft_strncmp(name, lst->name, name_len + 1))
		return (NULL);
	while (!ft_strncmp(name, lst->next->name, name_len + 1))
		lst = lst->next;
	return (lst);
}

