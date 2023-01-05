/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:50:29 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/05 18:19:03 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_old_fd(t_cmd_lst *cmd, int type);
static int	get_new_fd(t_cmd_lst *cmd, int type);

int	update_fd(t_cmd_lst *cmd, int type)
{
	close_old_fd(cmd, type);
	if (!get_new_fd(cmd, type))
		return (0);
	return (1);
}

static void	close_old_fd(t_cmd_lst *cmd, int type)
{
	if ((type == TRUNCATE || type == APPEND) && cmd->output > 2)
		close(cmd->output);
	else if ((type == INPUT || type == HEREDOC) && cmd->input > 2)
		close(cmd->input);
}

static int	get_new_fd(t_cmd_lst *cmd, int type)
{
	if (type == INPUT)
		cmd->input = open(cmd->filename, O_RDONLY, 0666);
	else if (type == HEREDOC)
	{
		if (cmd->delimiter)
			free(cmd->delimiter);
		cmd->delimiter = ft_strdup(cmd->filename);
		if (!check_heredoc(cmd))
			return (0);
	}
	else if (type == TRUNCATE)
		cmd->output = open(cmd->filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (type == APPEND)
		cmd->output = open(cmd->filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	return (1);
}
