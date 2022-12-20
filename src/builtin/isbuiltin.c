/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/19 18:38:29 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static void run_builtin(t_cmd_lst *cmd);
int is_builtin(t_cmd_lst *cmd, t_var_lst *env_lst)
{
	if (!ft_strncmp(cmd->args[0], "echo", 4))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "pwd", 3))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "export", 6))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "env", 3))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "exit", 3))
		return (1);
	else
		return (0);
	// free_matrix(cmd);
	return (1);
}

static void run_builtin(t_cmd_lst *cmd)
{
	int pid;

	pid = fork();
	if (!pid)
		echo(cmd);
}
