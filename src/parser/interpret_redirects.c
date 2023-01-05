/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:47:16 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/05 18:16:27 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	fill_filename(char *filename, char *line);
static void	get_filename(t_cmd_lst *cmd, char *line);
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
			if (cmd->filename)
				free(cmd->filename);
			get_filename(cmd, line);
			if (whitespace_checker(cmd->filename))
			{
				print_syntax_error(cmd, line);
				return (0);
			}
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

static void	get_filename(t_cmd_lst *cmd, char *line)
{
	int		chunk_size;
	int		file_size;

	get_sizes(line, &chunk_size, &file_size);
	cmd->filename = malloc(sizeof(char) * (file_size + 1));
	fill_filename(cmd->filename, line);
	remove_quotes(cmd->filename);
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
