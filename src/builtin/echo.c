/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:26 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/15 17:36:30 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	echo(t_cmd_lst *cmd)
{
	printf("entrou echo\n");
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
	while(cmd->args[content_index])
	{
		ft_putstr_fd(cmd->args[content_index], cmd->output);
		if (cmd->args[content_index + 1])
			write(cmd->output, " ", 1);
		content_index++;
	}
	if (trailing_newline)
		write(cmd->output, "\n", 1);
	return ;
}
