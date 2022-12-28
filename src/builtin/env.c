/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:00:18 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/27 21:55:40 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int env(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	int status;

	if (!check_heredoc(cmd))
		return (0);
	cmd->pid = fork();
	if (!cmd->pid)
	{
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
	g_exit_status = WEXITSTATUS(status);
	return (1);
}
