/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:53:23 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/25 15:55:59 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int exec_builtin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "echo", 4))
		echo(cmd, data);
	else if (!ft_strncmp(cmd->args[0], "cd", 2))
		cd(cmd, data, *env_lst);
	else if (!ft_strncmp(cmd->args[0], "pwd", 3))
		pwd(cmd, data);
	else if (!ft_strncmp(cmd->args[0], "export", 6))
		export(cmd, data, *env_lst);
	else if (!ft_strncmp(cmd->args[0], "unset", 5))
		unset(cmd, data, env_lst);
	else if (!ft_strncmp(cmd->args[0], "env", 3))
		env(cmd, data, *env_lst);
	else if (!ft_strncmp(cmd->args[0], "exit", 4))
		ft_exit(cmd, data);
	else
		return (0);
	return (1);
}

int is_builtin(char *cmd_name)
{
	if (!ft_strncmp(cmd_name, "echo", 4))
		return (1);
	else if (!ft_strncmp(cmd_name, "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd_name, "pwd", 3))
		return (1);
	else if (!ft_strncmp(cmd_name, "export", 6))
		return (1);
	else if (!ft_strncmp(cmd_name, "unset", 5))
		return (1);
	else if (!ft_strncmp(cmd_name, "env", 3))
		return (1);
	else if (!ft_strncmp(cmd_name, "exit", 3))
		return (1);
	else
		return (0);
}
