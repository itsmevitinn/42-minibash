/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/30 00:29:08 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

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
	g_running_process = 0;
}
