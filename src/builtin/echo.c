/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:26 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/22 11:49:24 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void echo(t_cmd_lst *cmd)
{
	int content_index;
	int trailing_newline;
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
		ft_putstr_fd(cmd->args[content_index], cmd->output);
		if (cmd->args[content_index + 1])
			write(cmd->output, " ", 1);
		content_index++;
	}
	if (trailing_newline)
		write(cmd->output, "\n", 1);
	g_exit_status = 0;
}
