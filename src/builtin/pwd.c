/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:00 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/24 17:47:26 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void pwd(t_cmd_lst *cmd, t_cmd_info *data)
{
	int status;
	
	cmd->pid = fork();
	if (!cmd->pid)
	{
		char *pwd;
		restore_sigint();
		if (cmd->delimiter)
			get_heredoc_input(cmd);
		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, cmd->output);
		ft_putchar_fd('\n', cmd->output);
		free(pwd);
		exit(0);
	}
	if (cmd->id < (data->qty - 1))
		close(data->pipes[cmd->id][1]);
	waitpid(cmd->pid, &status, 0);
	if (!WIFEXITED(status))
		return;
	else
		g_exit_status = WEXITSTATUS(status);
}