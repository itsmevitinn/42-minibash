/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:26 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/21 23:48:33 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void echo(t_cmd_lst *cmd, t_cmd_info *data)
{
	int status;
	// int pid;

	data->pid[cmd->id] = fork();
	if (!data->pid[cmd->id])
	{
		int content_index;
		int trailing_newline;
		dup2(cmd->input, 0);
		dup2(cmd->output, 1);
		if (data->qty >= 2)
			close_all_pipes(data->pipes);
		trailing_newline = 1;
		if (!ft_strncmp(cmd->args[1], "-n", 2) && ft_strlen(cmd->args[1]) == 2)
		{
			content_index = 2;
			trailing_newline = 0;
		}
		else
			content_index = 1;
		while (cmd->args[content_index])
		{
			ft_putstr_fd(cmd->args[content_index], 1);
			if (cmd->args[content_index + 1])
				write(1, " ", 1);
			content_index++;
		}
		if (trailing_newline)
			write(1, "\n", 1);
		exit(0);
	}
}
