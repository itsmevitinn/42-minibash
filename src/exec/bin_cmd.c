/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/20 19:01:17 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	exec_bin_cmd(char *full_path, t_cmd_lst *cmd)
// {
// 	int	pid;
// 	int status;

// 	pid = fork();
// 	if (!pid)
// 		execve(full_path, cmd->args, NULL);
// 	wait(&status);
// 	g_exit_status = WEXITSTATUS(status);
// 	//free right path after execution
// 	free(full_path);
// 	// free_matrix(cmd->args);
// }

void exec_bin_cmd(t_cmd_lst *cmd)
{
	char **paths;
	char *full_path;
	int i;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/", 1);
		full_path = ft_strjoin(full_path, cmd->args[0], 1);
		if (!access(full_path, F_OK | X_OK))
		{
			ft_putstr_fd("running execve\n", 2);
			execve(full_path, cmd->args, NULL);
		}
		// free wrong path
		free(full_path);
		i++;
	}
	free_paths(paths, i);
	exit(1);
}
