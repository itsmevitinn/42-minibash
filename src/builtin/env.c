/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:00:18 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/24 17:54:42 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void env(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	int status;

	cmd->pid = fork();
	if (!cmd->pid)
	{
		restore_sigint();
		if (cmd->delimiter)
			get_heredoc_input(cmd);
		while (env_lst)
		{
			if (env_lst->content)
			{
				ft_putstr_fd(env_lst->name, cmd->output);
				write(cmd->output, "=", 1);
				ft_putstr_fd((char *)env_lst->content, cmd->output);
				write(cmd->output, "\n", 1);
			}
			env_lst = env_lst->next;
		}
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