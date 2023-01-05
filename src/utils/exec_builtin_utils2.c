/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:07:14 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/04 22:07:21 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
