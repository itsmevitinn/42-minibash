/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:08:25 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/05 16:36:26 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_vars(t_var_lst *env_lst, int fd);
static void	export_var(t_var_lst *env_lst, char *cmd);
static int	name_is_invalid(char *cmd);
static void	exec_export(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);

int	export(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	if (data->qty != 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
			exec_export(cmd, data, env_lst);
		finish_fork_builtin(cmd);
	}
	else
		exec_export(cmd, data, env_lst);
	return (1);
}

static void	exec_export(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	char	**args;

	args = cmd->args;
	args++;
	if (!*args)
		print_vars(env_lst, cmd->output);
	while (*args)
	{
		if (name_is_invalid(*args))
		{
			print_invalid_identifier(*args, "export");
			if (data->qty > 1)
				exit(1);
			g_exit_status = 1;
			break ;
		}
		else
			export_var(env_lst, *args);
		args++;
	}
	if (data->qty > 1)
		exit(0);
}

static void	print_vars(t_var_lst *env_lst, int fd)
{
	int	should_print;

	while (env_lst)
	{
		should_print = ft_strncmp("_", env_lst->name, 2);
		if (should_print)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(env_lst->name, fd);
		}
		if (should_print && env_lst->content)
		{
			write(fd, "=\"", 2);
			ft_putstr_fd(env_lst->content, fd);
			write(fd, "\"", 1);
		}
		if (should_print)
			write(fd, "\n", 1);
		env_lst = env_lst->next;
	}
}

static int	name_is_invalid(char *cmd)
{
	if (*cmd == '=')
		return (1);
	while (*cmd && *cmd != '=')
	{
		if (!ft_isalpha(*cmd) && *cmd != '_')
			return (1);
		cmd++;
	}
	return (0);
}

static void	export_var(t_var_lst *env_lst, char *cmd)
{
	char	*content;
	char	*name;
	char	*aux;

	content = ft_strchr(cmd, '=');
	if (content)
	{
		name = malloc(content - cmd + 1);
		aux = name;
		while (cmd != content)
			*aux++ = *cmd++;
		*aux = '\0';
		content = ft_strdup(content + 1);
	}
	else
		name = ft_strdup(cmd);
	if (get_env(name, env_lst))
		change_content(name, content, env_lst);
	else
		ft_varadd_back(&env_lst, ft_var_new(name, content));
	g_exit_status = 0;
}
