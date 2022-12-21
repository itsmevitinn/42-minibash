/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/21 18:41:53 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void exec_bin_cmd(t_cmd_lst *cmd, int **pipes)
{
	int status;
	int pid;

	pid = fork();
	if (!pid)
	{
		char **paths;
		char *full_path;
		int i;
		if (cmd->input != 0)
			dup2(cmd->input, 0);
		else if (cmd->output != 1)
			dup2(cmd->output, 1);
		close_all_pipes(pipes);
		i = 0;
		paths = ft_split(getenv("PATH"), ':');
		while (paths[i])
		{
			full_path = ft_strjoin(paths[i], "/", 1);
			full_path = ft_strjoin(full_path, cmd->args[0], 1);
			if (!access(full_path, F_OK | X_OK))
			{
				printf("running execve\n");
				execve(full_path, cmd->args, NULL);
			}
			// free wrong path
			free(full_path);
			i++;
		}
		free_paths(paths, i);
		exit(1);
	}
	wait(&status);
	g_exit_status = WEXITSTATUS(status);
}
