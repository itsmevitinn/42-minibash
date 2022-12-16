/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:10:05 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/16 19:28:02 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void print_cmd(char **splitted_cmd);
void remove_chunk(char *cmd_line, int len);
static void cmd_notfound(char *cmd_name);
static void free_paths(char **paths, int i);
static void build_lst_cmd(t_cmd_lst *lst_cmd, char *line);
void initialize_std_fd(t_cmd_lst *lst_cmd);
void get_filename(t_cmd_lst *cmd, char *line, char type);
void redirect_checker(t_cmd_lst *cmd, char *line);
int file_exists(t_cmd_lst *cmd, char *filename, int type);
void get_sizes(char *line, int *chunk_size, int *file_size);
void fill_filename(char *filename, char *start_file);
void file_notfound(char *filename);
void change_fd(t_cmd_lst *cmd, int file_fd, char type);

void parse_input(char *line, t_var_lst *env_lst)
{
	env_lst++;
	t_cmd_lst *lst_cmd;

	lst_cmd = NULL;
	build_lst_cmd(lst_cmd, line);
	// find_right_path(splitted_cmd);
}

static void build_lst_cmd(t_cmd_lst *lst_cmd, char *line)
{
	char **all_cmds;
	int offset;

	lst_cmd = NULL;
	all_cmds = ft_split_quotes(line, '|');
	offset = 0;
	while (all_cmds[offset])
		ft_cmdadd_back(&lst_cmd, ft_cmd_new(all_cmds[offset++]));
	initialize_std_fd(lst_cmd);
	while (lst_cmd)
	{
		printf("command: %s\n", lst_cmd->line);
		redirect_checker(lst_cmd, lst_cmd->line);
		lst_cmd->args = ft_split_quotes(lst_cmd->line, ' ');
		print_cmd(lst_cmd->args);
		// is_builtin(lst_cmd, NULL);
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
	if (file_exists(cmd, filename, type))
		remove_chunk(line, chunk_size);
}

void file_notfound(char *filename)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(1);
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

int file_exists(t_cmd_lst *cmd, char *filename, int type)
{
	int file_fd;

	file_fd = 0;
	if (type == '<')
		file_fd = open(filename, O_RDONLY, 0666);
	else if (type == '>')
		file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (file_fd == -1)
		file_notfound(filename);
	change_fd(cmd, file_fd, type);
	return (1);
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
			close(cmd->input);
		cmd->output = file_fd;
	}
}

void remove_chunk(char *line, int len)
{
	char *aux;

	while (len >= 0)
	{
		aux = line;
		while (*aux)
		{
			*aux = aux[1];
			aux++;
		}
		len--;
	}
}

// static char **split_pipes(char *user_input)
// {
// 	char **all_cmds;

// 	all_cmds = ft_split_quotes(user_input, '|');
// 	build_lst_cmd(all_cmds);
// 	return (NULL);
// cmd = ft_split_quotes(cmd[0], ' ');
// while (cmd[args++])
// Cut the quotes at the edges of each arguments
// cmd[args] = ft_strtrim_edges(cmd[args], "'\"");
// return (cmd);
// }

void find_right_path(char **splitted_cmd)
{
	char **paths;
	char *full_path;
	int i;
	int success;

	i = 0;
	success = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/", 1);
		full_path = ft_strjoin(full_path, splitted_cmd[0], 1);
		if (!access(full_path, F_OK | X_OK))
		// right path found
		{
			exec_bin_cmd(full_path, splitted_cmd);
			success = 1;
			break;
		}
		// free wrong path
		free(full_path);
		i++;
	}
	if (!success)
		cmd_notfound(splitted_cmd[0]);
	free_paths(paths, i);
}

static void cmd_notfound(char *cmd_name)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit_status = 127;
}

static void free_paths(char **paths, int i)
{
	// we iterate here because the current "i" was already freed by strjoin
	while (paths[i++])
		free(paths[i]);
	free(paths);
}

static void print_cmd(char **splitted_cmd)
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
