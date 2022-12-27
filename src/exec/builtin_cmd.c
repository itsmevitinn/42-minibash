/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:53:23 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/27 01:16:17 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int exec_builtin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "echo", 4))
	{
		if (!echo(cmd, data))
			return (0);
	}
	else if (!ft_strncmp(cmd->args[0], "cd", 2))
	{
		if (!cd(cmd, data, *env_lst))
			return (0);
	}
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
	return (1);
}
