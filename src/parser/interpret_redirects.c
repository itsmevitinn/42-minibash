/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:47:16 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/06 12:21:10 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	fill_filename(char *filename, char *line);
static void	get_filename(t_cmd_lst *cmd, char *line, int type);
static void	get_sizes(char *line, int *chunk_size, int *file_size);
static int	get_type(char *line);

int	interpret_redirects(t_cmd_lst *cmd, char *line)
{
	int	type;

	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			line = skip_quote(line);
		else if (*line == '<' || *line == '>')
		{
			type = get_type(line);
			get_filename(cmd, line, type);
			if (has_syntax_error(type, line, cmd))
				return (0);
			if (!update_fd(cmd, type))
				return (0);
		}
		else
			line++;
	}
	return (1);
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
		return (write(2, "impossible else if at get_type function\n", 40));
}

static void	get_filename(t_cmd_lst *cmd, char *line, int type)
{
	int		chunk_size;
	int		file_size;
	char	*file;

	if (type == HEREDOC || type == INPUT)
		file = cmd->in_file;
	else
		file = cmd->out_file;
	if (file)
		free(file);
	get_sizes(line, &chunk_size, &file_size);
	file = malloc(sizeof(char) * (file_size + 1));
	fill_filename(file, line);
	remove_quotes(file);
	if (type == HEREDOC || type == INPUT)
		cmd->in_file = file;
	else
		cmd->out_file = file;
	remove_chunk(line, chunk_size);
}

static void	get_sizes(char *line, int *chunk_size, int *file_size)
{
	*chunk_size = 0;
	*file_size = 0;
	if (*line == line[1])
	{
		(*chunk_size)++;
		line++;
	}
	line++;
	while (*line && ft_isspace(*line) && *line != '<' && *line != '>')
	{
		(*chunk_size)++;
		line++;
	}
	while (*line && !ft_isspace(*line) && *line != '<' && *line != '>')
	{
		line++;
		(*chunk_size)++;
		(*file_size)++;
	}
}

static void	fill_filename(char *filename, char *line)
{
	char	*temp;

	temp = filename;
	if (*line == line[1])
		line++;
	line++;
	while (*line && ft_isspace(*line) && *line != '<' && *line != '>')
		line++;
	while (*line && !ft_isspace(*line) && *line != '<' && *line != '>')
		*temp++ = *line++;
	*temp = '\0';
}
