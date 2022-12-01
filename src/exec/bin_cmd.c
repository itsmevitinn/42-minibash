/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/30 23:11:11 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	free_cmd(char **splitted_cmd);
void	exec_bin_cmd(char *full_path, char **splitted_cmd)
{
	int	process_pid;

	process_pid = fork();
	g_running_process = 1;
	if (!process_pid)
		execve(full_path, splitted_cmd, NULL);
	waitpid(process_pid, NULL, 0);
	//free right path after execution
	free(full_path);
	free_cmd(splitted_cmd);
	g_running_process = 0;
}

static void	free_cmd(char **splitted_cmd)
{
	int i;

	i = 0;
	while(splitted_cmd[i])
		free(splitted_cmd[i++]);
	free(splitted_cmd);
}
