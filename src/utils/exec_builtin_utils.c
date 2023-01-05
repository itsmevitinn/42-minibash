/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:01:10 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/04 22:01:48 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	try_echo_execution(t_cmd_lst *cmd)
{
	if (!ft_strncmp(cmd->args[0], "echo", 4))
	{
		if (!echo(cmd))
			return (0);
	}
	return (1);
}

int	try_cd_execution(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "cd", 2))
	{
		if (!cd(cmd, data, *env_lst))
			return (0);
	}
	return (1);
}

int	try_pwd_execution(t_cmd_lst *cmd)
{
	if (!ft_strncmp(cmd->args[0], "pwd", 3))
	{
		if (!pwd(cmd))
			return (0);
	}
	return (1);
}

int	try_export_execution(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "export", 6))
	{
		if (!export(cmd, data, *env_lst))
			return (0);
	}
	return (1);
}

int	try_unset_execution(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "unset", 5))
	{
		if (!unset(cmd, data, env_lst))
			return (0);
	}
	return (1);
}

int	try_env_execution(t_cmd_lst *cmd, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "env", 3))
	{
		if (!env(cmd, *env_lst))
			return (0);
	}
	return (1);
}

int	try_exit_execution(t_cmd_lst *cmd, t_cmd_info *data)
{
	if (!ft_strncmp(cmd->args[0], "exit", 4))
	{
		if (!ft_exit(cmd, data))
			return (0);
	}
	return (1);
}
