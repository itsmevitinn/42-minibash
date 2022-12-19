/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:10:05 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/19 13:13:17 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void remove_chunk(char *cmd_line, int len);
static void free_paths(char **paths, int i);
static void build_lst_cmd(t_cmd_lst *lst_cmd, char *line, t_var_lst *env_lst);
void initialize_std_fd(t_cmd_lst *lst_cmd);
void get_filename(t_cmd_lst *cmd, char *line, char type);
void redirect_checker(t_cmd_lst *cmd, char *line);
void open_file(t_cmd_lst *cmd, char *filename, int type);
void get_sizes(char *line, int *chunk_size, int *file_size);
void fill_filename(char *filename, char *start_file);
void change_fd(t_cmd_lst *cmd, int file_fd, char type);
int syntax_checker(char *filename);

t_cmd_lst *parse_input(char *line, t_var_lst *env_lst)
{
	t_cmd_lst *lst_cmd;

	lst_cmd = NULL;
	build_lst_cmd(lst_cmd, line, env_lst);
	return (lst_cmd);
}

static void build_lst_cmd(t_cmd_lst *lst_cmd, char *line, t_var_lst *env_lst)
{
	char **all_cmds;
	char **temp;

	all_cmds = ft_split_quotes(line, '|');

	while (*all_cmds)
		ft_cmdadd_back(&lst_cmd, ft_cmd_new(*all_cmds++));
	initialize_std_fd(lst_cmd);
	while (lst_cmd)
	{
		redirect_checker(lst_cmd, lst_cmd->line);
		lst_cmd->args = ft_split_quotes(lst_cmd->line, ' ');
		temp = lst_cmd->args;
		while (*temp)
		{
			interpret_vars(temp, env_lst);
			cleanup(*temp);
			temp++;
		}
		print_matrix(lst_cmd->args);
		printf("fd input from %s: %i\n", lst_cmd->args[0], lst_cmd->input);
		printf("fd output from %s: %i\n", lst_cmd->args[0], lst_cmd->output);
		lst_cmd = lst_cmd->next;
	}
}

void initialize_std_fd(t_cmd_lst *lst_cmd)
{
	while (lst_cmd)
	{
		lst_cmd->input = 0;
		lst_cmd->output = 1;
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

void find_right_path(char **splitted_cmd)
{
	char **paths;
	char *full_path;
	int i;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/", 1);
		full_path = ft_strjoin(full_path, splitted_cmd[0], 1);
		if (!access(full_path, F_OK | X_OK))
		// right path found
		{
			exec_bin_cmd(full_path, splitted_cmd);
			break;
		}
		// free wrong path
		free(full_path);
		i++;
	}
	free_paths(paths, i);
}

static void free_paths(char **paths, int i)
{
	// we iterate here because the current "i" was already freed by strjoin
	while (paths[i++])
		free(paths[i]);
	free(paths);
}

void print_matrix(char **splitted_cmd)
{
	int i;

	i = 0;
	while (splitted_cmd[i])
	{
		printf("[%i] %s ", i, splitted_cmd[i]);
		i++;
	}
	printf("\n");
}
