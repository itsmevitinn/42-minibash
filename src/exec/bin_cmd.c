/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/24 18:35:42 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int 	exec_bin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	int status;

	cmd->pid = fork();
	if (!cmd->pid)
	{
		char **paths;
		char *full_path;
		int i;
		restore_sigint();
		if (cmd->delimiter)
			get_heredoc_input(cmd);
		dup2(cmd->input, 0);
		dup2(cmd->output, 1);
		if (data->qty >= 2)
			close_all_pipes(data);
		i = 0;
		paths = ft_split(get_content("PATH", env_lst), ':');
		while (paths[i])
		{
			if (!access(cmd->args[0], F_OK | X_OK))
				execve(cmd->args[0], cmd->args, NULL);
			full_path = ft_strjoin(paths[i], "/", 1);
			full_path = ft_strjoin(full_path, cmd->args[0], 1);
			if (!access(full_path, F_OK | X_OK))
				execve(full_path, cmd->args, NULL);
			// free wrong path
			free(full_path);
			i++;
		}
		free_paths(paths, i);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (cmd->id < (data->qty - 1))
		close(data->pipes[cmd->id][1]);
	waitpid(cmd->pid, &status, 0);
	if (!WIFEXITED(status))
		return (0);
	else
		g_exit_status = WEXITSTATUS(status);
	return(1);
}