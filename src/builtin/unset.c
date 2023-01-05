/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:10:07 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/05 11:18:14 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int			name_is_invalid(char *cmd);
static void			remove_var(t_var_lst **var_lst, char *name);
static t_var_lst	*get_previous(char *name, t_var_lst *lst);
static void			exec_unset(t_cmd_lst *cmd, t_cmd_info *data,
						t_var_lst **env_lst);

int	unset(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!check_heredoc(cmd))
		return (0);
	if (data->qty != 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
			exec_unset(cmd, data, env_lst);
		finish_fork_builtin(cmd);
	}
	else
		exec_unset(cmd, data, env_lst);
	return (1);
}

static void	exec_unset(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	char	**args;

	args = cmd->args;
	args++;
	while (*args)
	{
		if (name_is_invalid(*args))
		{
			print_invalid_identifier(*args, "unset");
			if (data->qty > 1)
				exit(1);
			g_exit_status = 1;
			break ;
		}
		else if (get_env(*args, *env_lst))
			remove_var(env_lst, *args);
		args++;
	}
	if (data->qty > 1)
		exit(0);
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

static void	remove_var(t_var_lst **var_lst, char *name)
{
	t_var_lst	*previous;
	t_var_lst	*temp;

	if (!ft_strncmp(name, "_", 2))
		return ;
	previous = get_previous(name, *var_lst);
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
	g_exit_status = 0;
}

static t_var_lst	*get_previous(char *name, t_var_lst *lst)
{
	int	name_len;

	name_len = ft_strlen(name);
	if (!ft_strncmp(name, lst->name, name_len + 1))
		return (NULL);
	while (ft_strncmp(name, lst->next->name, name_len + 1))
		lst = lst->next;
	return (lst);
}
