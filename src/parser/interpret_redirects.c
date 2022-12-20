/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:47:16 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/20 18:59:35 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void fill_filename(char *filename, char *line);
static char *get_filename(t_cmd_lst *cmd, char *line, char type);
static void get_sizes(char *line, int *chunk_size, int *file_size);
static void open_file(t_cmd_lst *cmd, char *filename, int type);
static void change_fd(t_cmd_lst *cmd, int file_fd, char type);

void	interpret_redirects(t_cmd_lst *cmd, char *line)
{
	while (*line)
	{
		if (*line == '<' || *line == '>')
		{
			cmd->filename = get_filename(cmd, line, *line); //CHECAR SE JA TIHA FILENAME PARA DAR FREE
			update_fd(cmd, *line);
		}
		else
			line++;
	}
}

static char *get_filename(t_cmd_lst *cmd, char *line, char type)
{
	char *filename;
	int chunk_size;
	int file_size;

	get_sizes(line, &chunk_size, &file_size);
	filename = malloc(sizeof(char) * (file_size + 1));
	fill_filename(filename, line);
	remove_chunk(line, chunk_size);
	printf("filename value: %s\n", filename);
	open_file(cmd, filename, type);
	return (filename);
}

static void get_sizes(char *line, int *chunk_size, int *file_size)
{
	*chunk_size = 0;
	*file_size = 0;
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
	line++;
	while (*line && ft_isspace(*line) && *line != '<' && *line != '>')
		line++;
	while (*line && !ft_isspace(*line) && *line != '<' && *line != '>')
		*temp++ = *line++;
	*temp = '\0';
}

static void	update_fd(t_cmd_lst *cmd, char typee)
{
	if (tpyr == )
}

static void open_file(t_cmd_lst *cmd, char *filename, int type)
{
	int file_fd;

	file_fd = 0;
	if (type == '<')
		file_fd = open(filename, O_RDONLY, 0666);
	else if (type == '>')
		file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	change_fd(cmd, file_fd, type);
}

static void change_fd(t_cmd_lst *cmd, int file_fd, char type)
{
	if (type == '<')
	{
		if (cmd->input != 0)
			close(cmd->input);
		cmd->input = file_fd;
	}
	else if (type == '>')
	{
		if (cmd->output != 1)
			close(cmd->output);
		cmd->output = file_fd;
	}
}
