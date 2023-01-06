/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:53:23 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/06 17:21:09 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "echo", 4))
		echo(cmd);
	else if (!ft_strncmp(cmd->args[0], "cd", 2))
		cd(cmd, data, *env_lst);
	else if (!ft_strncmp(cmd->args[0], "pwd", 3))
		pwd(cmd);
	else if (!ft_strncmp(cmd->args[0], "export", 6))
		export(cmd, data, *env_lst);
	else if (!ft_strncmp(cmd->args[0], "unset", 5))
		unset(cmd, data, env_lst);
	else if (!ft_strncmp(cmd->args[0], "env", 3))
		env(cmd, *env_lst);
	else if (!ft_strncmp(cmd->args[0], "exit", 4))
		ft_exit(cmd, data, *env_lst);
}
