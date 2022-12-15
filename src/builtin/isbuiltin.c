/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/15 17:31:40 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static void	run_builtin(t_cmd_lst *cmd);
int	is_builtin(t_cmd_lst *cmd, t_var_lst *env_lst)
{
	env_lst++;
	if (!ft_strncmp(cmd->args[0], "echo", 4))
		run_builtin(cmd);
		// echo(splitted_cmd, 1);
	// else if (!ft_strncmp(splitted_cmd[0], "cd", 2))
	// 	cd(splitted_cmd, env_lst);
	// else if (!ft_strncmp(splitted_cmd[0], "pwd", 3))
	// 	pwd(1);
	// else if (!ft_strncmp(splitted_cmd[0], "export", 6))
	// 	export(splitted_cmd, env_lst, 1);
	// else if (!ft_strncmp(splitted_cmd[0], "unset", 5))
	// 	pwd(1);
	// else if (!ft_strncmp(splitted_cmd[0], "env", 3))
	// 	env(env_lst, 1);
	// else if (!ft_strncmp(splitted_cmd[0], "exit", 3))
	// 	ft_exit(splitted_cmd);
	else
		return (0);
	// free_matrix(splitted_cmd);
	return (1);
}

static void	run_builtin(t_cmd_lst *cmd)
{
	int pid;

	pid = fork();
	if (!pid)
		echo(cmd);
}
