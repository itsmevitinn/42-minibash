/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:50:29 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/21 18:34:27 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inlcude/minishell.h"

static int	get_type(char *line);

void	update_fd(t_cmd_lst *cmd, char *line)
{
	int	type;
	
	type = get_type(line);
	close_old_fd(cmd, line);
	if (*type == '<' && cmd->input != 0)
		close(cmd->input);
	else if (*type == '>' && cmd->output != 1)
		close(cmd->output);
	if (*type == '<' && *type != type[1])
		cmd->input = open(cmd->filename, O_RDONLY, 0666);
	//else if (*type == '<' && *type == type[1])
	//	handle heredoc
	else if (*type == '>' && *type != type[1])
		cmd->output = open(cmd->filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (*type == '>' && *type == type[1])
		cmd->output = open(cmd->filename, O_CREAT | O_RDWR | O_APPEND, 0666);

}

static void	close_old_fd(t_cmd_lst *cmd, int type)
{
	if (type == TRUNCATE && cmd->output != 1)
		close(cmd->output);
	else if (type == APPEND && cmd->output != 1 && !cmd->has_truncate)
		close(cmd->output);
	else if (type == HEREDOC && cmd->input)
		close(cmd->input);
}

static int	get_type(char *line)
{
	if (*line == '<' && line[1] == *line)
		return (HEREDOC);
	else if (*line == '<')
		return (INPUT);
	else if (*line == '>' && line[1] == *line)
		return (APPEND);
	else if (*line == '>')
		return (TRUNCATE);
	else
		return (ft_putstr_fd("impossible else if at get_type function\n", 2));
}
