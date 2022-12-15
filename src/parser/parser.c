/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:10:05 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/15 18:00:28 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void print_cmd(char **splitted_cmd);
void remove_chunk(char *cmd_line, int len);
static void cmd_notfound(char *cmd_name);
static void free_paths(char **paths, int i);
static void build_lst_cmd(t_cmd_lst *lst_cmd, char *line);
void	initialize_std_fd(t_cmd_lst *lst_cmd);
void get_filename(t_cmd_lst *cmd, int offset, char type);
void redirect_checker(t_cmd_lst *lst_cmd);
int	check_file(t_cmd_lst *cmd, char *buffer, char type);
int	check_infile(t_cmd_lst *cmd, char *buffer);
int	check_outfile(t_cmd_lst *cmd, char *buffer);

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
		printf("line before:%s\n", lst_cmd->line);
		redirect_checker(lst_cmd);
		printf("line after: %s\n", lst_cmd->line);
		lst_cmd->args = ft_split_quotes(lst_cmd->line, ' ');
		print_cmd(lst_cmd->args);
		is_builtin(lst_cmd, NULL);
		lst_cmd = lst_cmd->next;
	}
}

void	initialize_std_fd(t_cmd_lst *lst_cmd)
{
	while(lst_cmd)
	{
		lst_cmd->input = 0;
		lst_cmd->output = 1;
		lst_cmd = lst_cmd->next;
	}
}

void redirect_checker(t_cmd_lst *cmd)
{
	int offset;

	offset = 0;
	while (cmd->line[offset])
	{
		if (cmd->line[offset] == '<' || cmd->line[offset] == '>')
			get_filename(cmd, offset, cmd->line[offset]);
		offset++;
	}
}

void get_filename(t_cmd_lst *cmd, int offset, char type)
{
	char *buffer;
	int filename;
	int len;
	int start_chunk;
	int buffer_offset;

	start_chunk = offset;
	buffer_offset = 0;
	len = 0;
	offset++;
	while (cmd->line[offset] && ft_isspace(cmd->line[offset]))
		offset++;
	filename = offset;
	while (cmd->line[offset] && !ft_isspace(cmd->line[offset]))
	{
		offset++;
		len++;
	}
	buffer = malloc(sizeof(char) * (len + 1));
	while (cmd->line[filename] && !ft_isspace(cmd->line[filename]))
		buffer[buffer_offset++] = cmd->line[filename++];
	buffer[buffer_offset] = '\0';
	if (check_file(cmd, buffer, type))
		remove_chunk(&cmd->line[start_chunk], offset - 1);
}

int	check_file(t_cmd_lst *cmd, char *buffer, char type)
{
	if (type == '<' && check_infile(cmd, buffer))
		return (1);
	else if (type == '>' && check_outfile(cmd, buffer))
		return (1);
	return (0);
}

int	check_infile(t_cmd_lst *cmd, char *buffer)
{
	int infile;
	
	infile = open(buffer, O_RDONLY, 0666);
	if (infile == -1)
		return (0);
	else
	{
		printf("new input fd from: %s\n", buffer);
		cmd->input = infile;
		printf("input fd: %d\n", cmd->input);
	}
	return (1);
}

int	check_outfile(t_cmd_lst *cmd, char *buffer)
{
	int outfile;

	outfile = open(buffer, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (outfile == -1)
		return (0);
	else
	{
		printf("new output fd from: %s\n", buffer);
		cmd->output = outfile;
		printf("output fd: %d\n", cmd->output);
	}
	return (1);
}

void remove_chunk(char *line, int len)
{
	printf("size: %i\n", len);
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
	exit_status = 127;
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
