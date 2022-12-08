/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/07 23:36:38 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_bin_cmd(char *full_path, char **splitted_cmd)
{
	int	pid;
	int status;

	pid = fork();
	if (!pid)
		execve(full_path, splitted_cmd, NULL);
	wait(&status);
	exit_status = WEXITSTATUS(status);
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
