/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:53:23 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/09 22:23:50 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if ((!ft_strncmp(cmd->args[0], "echo", 5)) || (!ft_strncmp(cmd->args[0],
				"/bin/echo", 10)))
		echo(cmd);
	else if ((!ft_strncmp(cmd->args[0], "cd", 3)) || (!ft_strncmp(cmd->args[0],
				"/usr/bin/cd", 12)))
		cd(cmd, data, *env_lst);
	else if ((!ft_strncmp(cmd->args[0], "pwd", 4)) || (!ft_strncmp(cmd->args[0],
				"/bin/pwd", 9)))
		pwd(cmd);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		export(cmd, data, *env_lst);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		unset(cmd, data, env_lst);
	else if ((!ft_strncmp(cmd->args[0], "env", 4)) || (!ft_strncmp(cmd->args[0],
				"/usr/bin/env", 13)))
		env(cmd, *env_lst);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ft_exit(cmd, data, *env_lst);
}
