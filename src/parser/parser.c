/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:10:05 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/20 18:06:50 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void build_lst_cmd(t_cmd_lst **lst_cmd, char *line, t_var_lst *env_lst);
void initialize_std_fd(t_cmd_lst *lst_cmd);
void get_filename(t_cmd_lst *cmd, char *line, char type);
void redirect_checker(t_cmd_lst *cmd, char *line);
void open_file(t_cmd_lst *cmd, char *filename, int type);
void get_sizes(char *line, int *chunk_size, int *file_size);
void fill_filename(char *filename, char *start_file);
void change_fd(t_cmd_lst *cmd, int file_fd, char type);

t_cmd_lst *parse_input(char *line, t_var_lst *env_lst)
{
	t_cmd_lst *lst_cmd;

	lst_cmd = NULL;
	build_lst_cmd(&lst_cmd, line, env_lst);
	return (lst_cmd);
}

static void build_lst_cmd(t_cmd_lst **lst_cmd, char *line, t_var_lst *env_lst)
{
	char **all_cmds;
	char **temp;
	t_cmd_lst *head;

	all_cmds = ft_split_quotes(line, '|');

	while (*all_cmds)
		ft_cmdadd_back(lst_cmd, ft_cmd_new(*all_cmds++));
	initialize_std_fd(*lst_cmd);
	head = *lst_cmd;
	while (head)
	{
		redirect_checker(head, head->line);
		head->args = ft_split_quotes(head->line, ' ');
		temp = head->args;
		while (*temp)
		{
			interpret_vars(temp, env_lst);
			cleanup(*temp);
			temp++;
		}
		print_matrix(head->args);
		head = head->next;
	}
}

void initialize_std_fd(t_cmd_lst *lst_cmd)
{
	int counter;

	counter = 0;
	while (lst_cmd)
	{
		lst_cmd->input = 0;
		lst_cmd->output = 1;
		lst_cmd->id = counter++;
		lst_cmd = lst_cmd->next;
	}
}

void redirect_checker(t_cmd_lst *cmd, char *line)
{
	while (*line)
	{
		if (*line == '<' || *line == '>')
			get_filename(cmd, line, *line);
		else
			line++;
	}
}

void get_filename(t_cmd_lst *cmd, char *line, char type)
{
	char *filename;
	int chunk_size;
	int file_size;

	chunk_size = 0;
	file_size = 0;
	get_sizes(line, &chunk_size, &file_size);
	filename = malloc(sizeof(char) * (file_size + 1));
	fill_filename(filename, line);
	cmd->filename = filename;
	printf("filename value: %s\n", cmd->filename);
	open_file(cmd, filename, type);
	remove_chunk(line, chunk_size);
}

void fill_filename(char *filename, char *line)
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

void get_sizes(char *line, int *chunk_size, int *file_size)
{
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

void open_file(t_cmd_lst *cmd, char *filename, int type)
{
	int file_fd;

	file_fd = 0;
	if (type == '<')
		file_fd = open(filename, O_RDONLY, 0666);
	else if (type == '>')
		file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	change_fd(cmd, file_fd, type);
}

void change_fd(t_cmd_lst *cmd, int file_fd, char type)
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
