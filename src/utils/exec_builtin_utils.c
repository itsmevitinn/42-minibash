/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:01:10 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/06 16:49:32 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	try_echo_execution(t_cmd_lst *cmd)
{
	if (!ft_strncmp(cmd->args[0], "echo", 4))
	{
		echo(cmd);
		return (1);
	}
	return (0);
}

int	try_cd_execution(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "cd", 2))
	{
		cd(cmd, data, *env_lst);
		return (1);
	}
	return (0);
}

int	try_pwd_execution(t_cmd_lst *cmd)
{
	if (!ft_strncmp(cmd->args[0], "pwd", 3))
	{
		pwd(cmd);
		return (1);
	}
	return (0);
}

int	try_export_execution(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "export", 6))
	{
		export(cmd, data, *env_lst);
		return (1);
	}
	return (0);
}

int	try_unset_execution(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "unset", 5))
	{
		unset(cmd, data, env_lst);
		return (1);
	}
	return (0);
}
