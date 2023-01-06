/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:07:14 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/06 16:48:34 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	try_env_execution(t_cmd_lst *cmd, t_var_lst **env_lst)
{
	if (!ft_strncmp(cmd->args[0], "env", 3))
	{
		env(cmd, *env_lst);
		return (1);
	}
	return (0);
}

int	try_exit_execution(t_cmd_lst *cmd, t_cmd_info *data)
{
	if (!ft_strncmp(cmd->args[0], "exit", 4))
	{
		ft_exit(cmd, data);
		return (1);
	}
	return (0);
}
