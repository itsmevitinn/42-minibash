/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:50:29 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/22 11:04:44 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	should_update(t_cmd_lst *cmd, int type);
static void	close_old_fd(t_cmd_lst *cmd, int type);
static void	get_new_fd(t_cmd_lst *cmd, int type);

void	update_fd(t_cmd_lst *cmd, int type)
{
	if (should_update(cmd, type))
	{
		close_old_fd(cmd, type);
		get_new_fd(cmd, type);
	}
}

static int	should_update(t_cmd_lst *cmd, int type)
{
	if (type == APPEND && cmd->has_truncate)
		return (0);
	else if (type == INPUT && cmd->heredoc_delimiter)
		return (0);
	else
		return (1);
}

static void	close_old_fd(t_cmd_lst *cmd, int type)
{
	if ((type == TRUNCATE || type == APPEND) && cmd->output != 1)
		close(cmd->output);
	else if ((type == INPUT || type == HEREDOC) && cmd->input)
		close(cmd->input);
}

static void	get_new_fd(t_cmd_lst *cmd, int type)
{
	if (type == INPUT)
		cmd->input = open(cmd->filename, O_RDONLY, 0666);
	else if (type == HEREDOC)
	{
		cmd->input = 0;
		if (cmd->heredoc_delimiter)
			free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = ft_strdup(cmd->filename);
	}
	else if (type == TRUNCATE)
		cmd->output = open(cmd->filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (type == APPEND)
		cmd->output = open(cmd->filename, O_CREAT | O_RDWR | O_APPEND, 0666);
}
