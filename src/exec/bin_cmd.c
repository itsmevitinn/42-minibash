/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/22 16:51:10 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exec_bin_cmd(t_cmd_lst *cmd, t_cmd_info *data)
{
	int status;

	data->pids[data->id] = fork();
	// cmd->pid = fork();
	// if (!cmd->pid)
	if (!data->pids[data->id++])
	{
		char **paths;
		char *full_path;
		int i;
		dup2(cmd->input, 0);
		dup2(cmd->output, 1);
		if (data->qty >= 2)
			close_all_pipes(data);
		i = 0;
		paths = ft_split(getenv("PATH"), ':');
		while (paths[i])
		{
			full_path = ft_strjoin(paths[i], "/", 1);
			full_path = ft_strjoin(full_path, cmd->args[0], 1);
			if (!access(full_path, F_OK | X_OK))
				execve(full_path, cmd->args, NULL);
			// free wrong path
			free(full_path);
			i++;
		}
		free_paths(paths, i);
		printf("Chegou aqui\n");
		exit(127);
	}
	// waitpid(cmd->pid, &status, 0);
	// g_exit_status = WEXITSTATUS(status);
}
