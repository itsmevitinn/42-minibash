/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/04 20:11:18 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	exec_bin_cmd(char *full_path, char **splitted_cmd)
{
	int	process_pid;

	process_pid = fork();
	if (!process_pid)
		execve(full_path, splitted_cmd, NULL);
	waitpid(process_pid, NULL, 0);
	//free right path after execution
	free(full_path);
	free_matrix(splitted_cmd);
}

void	free_matrix(char **splitted_cmd)
{
	int i;

	i = 0;
	while(splitted_cmd[i])
		free(splitted_cmd[i++]);
	free(splitted_cmd);
}
