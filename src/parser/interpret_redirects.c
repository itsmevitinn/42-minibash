/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:47:16 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/21 17:48:40 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void fill_filename(char *filename, char *line);
static void	get_filename(t_cmd_lst *cmd, char *line);
static void get_sizes(char *line, int *chunk_size, int *file_size);
static void	update_fd(t_cmd_lst *cmd, char *type);

void	interpret_redirects(t_cmd_lst *cmd, char *line)
{
	while (*line)
	{
		if (*line == '<' || *line == '>')
		{
			if (cmd->filename)
				free(cmd->filename);
			get_filename(cmd, line);
			printf("filename = %s\n", cmd->filename);
			update_fd(cmd, line);
		}
		else
			line++;
	}
}

static void	get_filename(t_cmd_lst *cmd, char *line)
{
	int		chunk_size;
	int		file_size;

	get_sizes(line, &chunk_size, &file_size);
	cmd->filename = malloc(sizeof(char) * (file_size + 1));
	fill_filename(cmd->filename, line);
	remove_chunk(line, chunk_size);
}

static void get_sizes(char *line, int *chunk_size, int *file_size)
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

static void fill_filename(char *filename, char *line)
{
	char *temp;

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

static void	update_fd(t_cmd_lst *cmd, char *type)
{
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
