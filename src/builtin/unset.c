/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:10:07 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/02 21:23:27 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int			name_is_invalid(char *cmd);
static void			remove_var(t_var_lst **var_lst, char *name);
static t_var_lst	*get_previous(char *name, t_var_lst *lst);
static void			print_error(char *cmd, int fd);

int	unset(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	char	**args;
	int		status;

	if (!check_heredoc(cmd))
		return (0);
	args = cmd->args;
	if (data->qty != 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
		{
			args++;
			while (*args)
			{
				if (name_is_invalid(*args))
				{
					print_error(*args, cmd->output);
					exit(1);
				}
				else if (get_env(*args, *env_lst))
					remove_var(env_lst, *args);
				args++;
			}
			exit(0);
		}
	}
	else
	{
		args++;
		while (*args)
		{
			if (name_is_invalid(*args))
			{
				print_error(*args, cmd->output);
				g_exit_status = 1;
			}
			else if (get_env(*args, *env_lst))
				remove_var(env_lst, *args);
			args++;
		}
		g_exit_status = 0;
	}
	waitpid(cmd->pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
	return (1);
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

static void	print_error(char *cmd, int fd)
{
	ft_putstr_fd("bash: unset `", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd("\': not a valid identifier\n", fd);
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
